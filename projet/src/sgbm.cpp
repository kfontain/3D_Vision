#include "headers/sgbm.h"
#include "headers/include.h"
#include "headers/convert.h"

cv::Mat g1, g2;
cv::Mat disp, disp8;
cv::StereoBM sbm;
int sad, nbdisp;

/// Cette fonction calcule la carte de disparité à partir des images sources en paramètres.
/// Cette fonction utilise l'algorithme SGBM.
/// left est la première image source.
/// right est la deuxième image source.
/// dst est l'image dans laquelle la carte de disparité sera sauvegardée.
void dispSGBM()
{
    using namespace cv;
    using namespace std;

    Mat img1, img2;

    sad = 0;
    nbdisp = 112;

    img1 = imread("left_1.png");
    img2 = imread("right_1.png");

    cvtColor(img1, g1, CV_BGR2GRAY);
    cvtColor(img2, g2, CV_BGR2GRAY);

    sbm.state->SADWindowSize = 2*sad+5; //Doit être impair est compris entre 5 et 255.
    sbm.state->numberOfDisparities = 112;
    sbm.state->preFilterSize = 5;
    sbm.state->preFilterCap = 61;
    sbm.state->minDisparity = -39;
    sbm.state->textureThreshold = 507;
    sbm.state->uniquenessRatio = 0;
    sbm.state->speckleWindowSize = 0;
    sbm.state->speckleRange = 8;
    sbm.state->disp12MaxDiff = 1;

    sbm(g1, g2, disp);
    normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
    namedWindow("SBM", WINDOW_NORMAL);
    imshow("SBM", disp8);

    std::string test = std::to_string(2*sad+1);
    //N'arrive pas à afficher la valeur.

    createTrackbar("SAD : " + test, "SBM", &sad, 125, update);
    //Reste les autres trackbar à finir en prenant en compte les valeurs min & max.
}

static void update(int, void*)
{
    //todo : delete previous sbm in "SBM" window.
    fprintf(stderr, "bonjour \n");
    sbm.state->SADWindowSize = 2*sad+1;
    sbm.state->numberOfDisparities = 112;
    sbm.state->preFilterSize = 5;
    sbm.state->preFilterCap = 61;
    sbm.state->minDisparity = -39;
    sbm.state->textureThreshold = 507;
    sbm.state->uniquenessRatio = 0;
    sbm.state->speckleWindowSize = 0;
    sbm.state->speckleRange = 8;
    sbm.state->disp12MaxDiff = 1;
    sbm(g1, g2, disp);
    normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
    imshow("SBM", disp8);
}
