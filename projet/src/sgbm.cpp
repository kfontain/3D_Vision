#include "headers/sgbm.h"
#include "headers/include.h"
#include "headers/convert.h"
#include "headers/edit.h"

cv::Mat g1, g2, g3, g4, g5, g6;
cv::Mat disp1, disp2, disp3, disp81, disp82, disp83;
cv::StereoSGBM sgbm;
int sad, nbdisp;
int mindisp;
int uniq;
int speckle;

static void update(int, void*)
{
    sgbm.SADWindowSize = 2*sad+5;
    sgbm.numberOfDisparities = 16*nbdisp + 16;
    sgbm.minDisparity = mindisp - 20;
    sgbm.uniquenessRatio = uniq;
    sgbm.speckleWindowSize = 50 + speckle;
    fprintf(stderr, "SADWindowSize : %d ", sgbm.SADWindowSize);
    fprintf(stderr, "numberOfDisparities : %d ", sgbm.numberOfDisparities);
    fprintf(stderr, "minDisparity : %d ", sgbm.minDisparity);
    fprintf(stderr, "uniquenessRatio : %d ", sgbm.uniquenessRatio);
    fprintf(stderr, "Speckle WindowSize : %d ", sgbm.speckleWindowSize);
    fprintf(stderr, "\n----------\n");

    sgbm.preFilterCap = 63;
    sgbm.speckleRange = 4;
    sgbm.disp12MaxDiff = 1;
    sgbm.fullDP = true;

    sgbm(g1, g2, disp1);
    sgbm(g3, g4, disp2);
    sgbm(g5, g6, disp3);

    normalize(disp1, disp81, 0, 255, CV_MINMAX, CV_8U);
    normalize(disp2, disp82, 0, 255, CV_MINMAX, CV_8U);
    normalize(disp3, disp83, 0, 255, CV_MINMAX, CV_8U);

    cv::Mat depth1, depth2, depth3;
    depthMap(disp81, &depth1);
    depthMap(disp82, &depth2);
    depthMap(disp83, &depth3);

    fprintf(stderr, "average 1 : %f\n",average(depth1));
    fprintf(stderr, "average 2 : %f\n",average(depth2));
    fprintf(stderr, "average 3 : %f\n",average(depth3));
}

/// Cette fonction calcule la carte de disparité à partir des images sources en paramètres.
/// Cette fonction utilise l'algorithme SGBM.
/// left est la première image source.
/// right est la deuxième image source.
/// dst est l'image dans laquelle la carte de disparité sera sauvegardée.
void dispSGBM()
{
    using namespace cv;
    using namespace std;

    Mat img1, img2, img3, img4, img5, img6;

    sad = 5;
    nbdisp = 1;
    mindisp = 36;
    uniq = 10;
    speckle = 150;

    // Images prises avec 7cm d'écarts entre les caméras.
    img1 = imread("left_2.png");
    img2 = imread("right_2.png");
    img3 = imread("left_1.png");
    img4 = imread("right_1.png");
    img5 = imread("left_0.png");
    img6 = imread("right_0.png");

    cvtColor(img1, g1, CV_BGR2GRAY);
    cvtColor(img2, g2, CV_BGR2GRAY);
    cvtColor(img3, g3, CV_BGR2GRAY);
    cvtColor(img4, g4, CV_BGR2GRAY);
    cvtColor(img5, g5, CV_BGR2GRAY);
    cvtColor(img6, g6, CV_BGR2GRAY);

    namedWindow("control panel", WINDOW_NORMAL);

    update(0, NULL);

    createTrackbar("SAD", "control panel", &sad, 125, update);
    createTrackbar("nb disp", "control panel", &nbdisp, 10, update);
    createTrackbar("min disp", "control panel", &mindisp, 70, update);
    createTrackbar("unique ratio", "control panel", &uniq, 20, update);
    createTrackbar("Speckle Wsize", "control panel", &speckle, 150, update);
}
