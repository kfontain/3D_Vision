#include "edit.h"
#include "convert.h"

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
///L'image post-sift est sauvegardée dans l'image dst entrée en paramètre.
void sift(cv::Mat src, cv::Mat *dst)
{
    cv::Mat tmp;
    cv::cvtColor(src, tmp, CV_BGR2GRAY);
    int minHessian = 400;
    cv::SurfFeatureDetector detector(minHessian);
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(tmp, keypoints);

    cv::drawKeypoints(tmp, keypoints, *dst, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
}
