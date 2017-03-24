#include "headers/sgbm.h"

/// Cette fonction calcule la carte de disparité à partir des images sources en paramètres.
/// Cette fonction utilise l'algorithme SGBM.
/// left est la première image source.
/// right est la deuxième image source.
/// dst est l'image dans laquelle la carte de disparité sera sauvegardée.
void dispSGBM()
{
    using namespace cv;
    using namespace std;

    Mat img1, img2, g1, g2;
    Mat disp, disp8;

    img1 = imread("left_1.png");
    img2 = imread("right_1.png");

    cvtColor(img1, g1, CV_BGR2GRAY);
    cvtColor(img2, g2, CV_BGR2GRAY);

    StereoBM sbm;
    sbm.state->SADWindowSize = 9;
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

    createTrackbar("SADWindowSize", "SBM", sbm.state->SADWindowSize, max_lowThreshold, dispSGBM() );
}
