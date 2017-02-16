#include "headers/edit.h"
#include "headers/convert.h"

///Cette fonction permet de couper l'image src entrée en paramètre en deux, au milieu.
///Les demi-images ainsi obtenues seront mises dans les paramètres left et right respectivement.
void split(QImage src, cv::Mat* left, cv::Mat* right)
{
    int width = src.width();
    int height = src.height();
    QRect rect1(0, 0, width/2, height);
    QRect rect2(width/2, 0, width/2, height);
    QImage original(src);
    QImage tmpLeft = original.copy(rect1);
    QImage tmpRight = original.copy(rect2);
    *left = qImage2Mat(tmpLeft, true);
    *right = qImage2Mat(tmpRight, true);
}

///Cette fonction permet de faire resortir les bords d'une image, en utilisant la fonction Sobel.
///L'image source est en paramètre : src.
///L'image post-détection de bords est sauvegardée dans l'image dsl en paramètre.
void sobel(cv::Mat src, cv::Mat *dst)
{
    //Convertie l'image source en niveau de gris.
    cv::Mat tmpGray;
    cv::cvtColor(src, tmpGray, CV_BGR2GRAY);

    //Déclaration des variables nécessaires à l'utilisation de la fonction Sobel.
    cv::Mat x, y;
    int scale = 1;
    int delta = 0;
    int depth = CV_16S;
    int kernelSize = 3;
    int border = cv::BORDER_DEFAULT;

    //La méthode Sobel calcule l'intensité relative d'un pixel à ses voisins.
    //src_gray est l'image source en niveau de gris, x et y sont les cv::Mat recevant le résultat.
    cv::Sobel(tmpGray, x, depth, 1, 0, kernelSize, scale, delta, border);
    cv::Sobel(tmpGray, y, depth, 0, 1, kernelSize, scale, delta, border);

    //Conversion en CV_8U. 8 bits non signés/pixel, format standard.
    //dx et dy sont les cv::Mat recevant le résultat de chaque appel.
    cv::Mat dx, dy;
    cv::convertScaleAbs(x, dx);
    cv::convertScaleAbs(y, dy);

    //addWeighted permet de faire une moyenne entre dx et dy.
    //0.5 et 0.5 sont les coefficients respectifs appliqués à dx et dy.
    //0 est un scalaire qui peut être ajouté (ici non utilisé).
    cv::Mat result;
    cv::addWeighted(dx, 0.5, dy, 0.5, 0, result);

    *dst = result;
}


///Cette fonction permet de détecter les features de l'image src entrée en paramètre.
///L'image post-surf est sauvegardée dans l'image dst entrée en paramètre.
void surf(cv::Mat src, cv::Mat *dst)
{
    cv::Mat tmp;
    cv::cvtColor(src, tmp, CV_BGR2GRAY);
    int minHessian = 400;
    cv::SurfFeatureDetector detector(minHessian);
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(tmp, keypoints);

    cv::drawKeypoints(tmp, keypoints, *dst, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
}

///Permet de faire l'appariement entre les points d'intérêts entre les 2 images en paramètres src et src2.
void surfMatch(cv::Mat src, cv::Mat src2, cv::Mat *dst)
{
    cv::Mat tmp, tmp2;
    cv::cvtColor(src, tmp, CV_BGR2GRAY);
    cv::cvtColor(src2, tmp2, CV_BGR2GRAY);

    int minHessian = 400;
    cv::SurfFeatureDetector detector(minHessian);
    std::vector<cv::KeyPoint> keypoints, keypoints2;
    detector.detect(tmp, keypoints);
    detector.detect(tmp2, keypoints2);

    cv::SurfDescriptorExtractor extractor;
    cv::Mat descriptor, descriptor2;

    extractor.compute(tmp, keypoints, descriptor);
    extractor.compute(tmp2, keypoints2, descriptor2);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(descriptor, descriptor2, matches);

    double maxDist = 0;
    double minDist = 100;

    for(int i = 0; i < descriptor.rows; i++)
    {
        double dist = matches[i].distance;
        if(dist < minDist) minDist = dist;
        if(dist > maxDist) maxDist = dist;
    }

    printf("Max Dist : %f \n", maxDist);
    printf("Min Dist : %f \n", minDist);

    std::vector<cv::DMatch> goodMatches;

    for( int i = 0; i < descriptor.rows; i++ )
    {
        if(matches[i].distance <= cv::max(2*minDist, 0.02))
        {
            goodMatches.push_back(matches[i]);
        }
    }

    cv::Mat imgMatches;
    cv::drawMatches(tmp, keypoints, tmp2, keypoints2,
                goodMatches, imgMatches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                cv::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    *dst = imgMatches;

}

///Cette fonction calcule la carte de disparité à partir des images sources en paramètres.
///src est la première image source.
///src2 est la deuxième image source.
///dst est l'image dans laquelle la carte de disparité sera sauvegardée.
void dispMap(cv::Mat src, cv::Mat src2, cv::Mat *dst)
{
    //Convertissement des images en niveau de gris.
    cv::Mat tmp, tmp2;
    cv::cvtColor(src, tmp, CV_BGR2GRAY);
    cv::cvtColor(src2, tmp2, CV_BGR2GRAY);

    //Création des images dans lesquelles les disparités seront sauvegardées. (même taille)
    cv::Mat imgDisp16S = cv::Mat(tmp.rows, tmp.cols, CV_16S);
    cv::Mat imgDisp8U = cv::Mat(tmp.rows, tmp.cols, CV_8UC1);

    //Création d'un StereoBM
    int preset = cv::StereoBM::BASIC_PRESET;
    int ndisparities = 16 * 2;
    int SADWindowSize = 31;

    cv::StereoBM sbm = cv::StereoBM(preset, ndisparities, SADWindowSize);

    sbm.operator()(tmp, tmp2, imgDisp16S, CV_16S);
    double min, max;
    minMaxLoc(imgDisp16S, &min, &max);

    imgDisp16S.convertTo(imgDisp8U, CV_8UC1, 255/(max - min));

    *dst = imgDisp8U;
}


///Cette fonction calcule la carte de profondeur à partir de la carte de disparité entrée en paramètre.
///src est la carte de disparité en entrée, doit être en niveau de gris.
///dst est l'image dans laquelle la carte de profondeur sera sauvegardée.
///Formule utilisée : EcartCamera * DistFocale / mapDisp(y,x)
void depthMap(cv::Mat src, cv::Mat *dst)
{
    int rows = src.rows;
    int cols = src.cols;

    //Valeurs prises au hasard pour l'instant.
    int ecart = 50;
    int focale = 100;

    cv::Mat tmp = cv::Mat(rows, cols, CV_8UC1);

    for (int j = 0; j < cols ; j++)
    {
        for (int i = 0; i < rows ; i++)
        {
            tmp.at<uchar>(i, j) = (ecart * focale) / (src.at<uchar>(i, j) +1);
        }
    }

    *dst = tmp;
}









