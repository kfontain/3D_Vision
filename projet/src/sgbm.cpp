#include "headers/sgbm.h"
#include "headers/include.h"
#include "headers/convert.h"

cv::Mat g1, g2;
cv::Mat disp, disp8;
cv::StereoBM sbm;
int sad, nbdisp;
int mindisp;
int uniq;

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

    sad = 8;
    nbdisp = 0;
    mindisp = 37;
    uniq = 14;

    img1 = imread("left_1.png"); //7cm
    img2 = imread("right_1.png");

    cvtColor(img1, g1, CV_BGR2GRAY);
    cvtColor(img2, g2, CV_BGR2GRAY);

    namedWindow("SBM", WINDOW_NORMAL);

    update(0, NULL);

    createTrackbar("SAD", "SBM", &sad, 125, update);
    createTrackbar("nb disp", "SBM", &nbdisp, 10, update);
    createTrackbar("min disp", "SBM", &mindisp, 70, update);
    createTrackbar("unique ratio", "SBM", &uniq, 20, update);
    //Reste les autres trackbar à finir en prenant en compte les valeurs min & max.
}

static void update(int, void*)
{
    sbm.state->SADWindowSize = 2*sad+5;
    sbm.state->numberOfDisparities = 16*nbdisp + 16;
    sbm.state->minDisparity = mindisp - 20;
    sbm.state->uniquenessRatio = uniq;
    fprintf(stderr, "SADWindowSize : %d ", sbm.state->SADWindowSize);
    fprintf(stderr, "numberOfDisparities : %d ", sbm.state->numberOfDisparities);
    fprintf(stderr, "minDisparity : %d ", sbm.state->minDisparity);
    fprintf(stderr, "uniquenessRatio : %d ", sbm.state->uniquenessRatio);
    fprintf(stderr, "\n----------\n");

    sbm.state->preFilterSize = 51;
    sbm.state->preFilterCap = 63;
    sbm.state->textureThreshold = 30;
    sbm.state->speckleWindowSize = 0;
    sbm.state->speckleRange = 4;
    sbm.state->disp12MaxDiff = 1;

    sbm(g1, g2, disp);
    normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
    imshow("SBM", disp8);
}
