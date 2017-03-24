#include "headers/mainwindow.h"
#include "headers/include.h"
#include "headers/sgbm.h"
#include <QApplication>
#include <string>
#include <sstream>

void disp(cv::Mat src, cv::Mat src2, cv::Mat *dst, int ndisparities, int SADWindowSize)
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

    cv::StereoBM sbm = cv::StereoBM(preset, ndisparities, SADWindowSize);

    sbm.operator()(tmp, tmp2, imgDisp16S, CV_16S);
    double min, max;
    minMaxLoc(imgDisp16S, &min, &max);

    imgDisp16S.convertTo(imgDisp8U, CV_8UC1, 255/(max - min));

    *dst = imgDisp8U;
}


int main(int argc, char *argv[])
{


    if (argc == 1) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    }

    if (atoi(argv[1]) == 0) {

        //fichier : camX-distY.png

        for (int j = 0 ; j < 3 ; j++) {
            for (int i = 0 ; i < 5 ; i++) {
                std::ostringstream ossI, ossO;
                ossI << "source/cam" << j << "-dist" << i << ".png"; //path fichier entrant
                ossO << "result/cam" << j << "-dist" << i << ".png"; //path fichier sortant
                std::string in = ossI.str();
                std::string out = ossO.str();

                //fichier en entrée
                cv::Mat src = cv::imread(in);
                QImage cnvt = mat2QImage(src, true);

                cv::Mat left, right;
                split(cnvt, &left, &right);
                cv::Mat tmp;
                dispMap(left, right, &tmp);
                cv::Mat result;
                //Applique un NON logique à chaque bit => Inverse les couleurs
                cv::bitwise_not(tmp, result);

                //fichier sortant
                cv::imwrite(out, result);
            }
        }
        return 0;
    }

    if (atoi(argv[1]) == 1) {
        printf("bonjour\n");
        for (int j = 4 ; j < 8 ; j++) {
            for (int i = 0 ; i < 4 ; i++) {
                std::ostringstream left_path, right_path, dst_path;
                left_path << "srcrobot/" << j << "cm/left_" << i << ".png"; //path fichier gauche entrant
                right_path << "srcrobot/" << j << "cm/right_" << i << ".png"; //path fichier droite entrant
                dst_path << "dstrobot/" << j << "cm/dist" << i << ".png"; //path fichier sortant
                std::string left_string = left_path.str();
                std::string right_string = right_path.str();
                std::string dst_string = dst_path.str();

                printf("accessing file %s \n", left_string.c_str());
                printf("accessing file %s \n", right_string.c_str());
                cv::Mat left = cv::imread(left_string);
                cv::Mat right = cv::imread(right_string);
                cv::Mat tmp;
                dispMap(left, right, &tmp);
                cv::Mat result;
                cv::bitwise_not(tmp, result);

                cv::imwrite(dst_string, result);
            }
        }
    }

    if (atoi(argv[1]) == 2) {
        printf("bonjour\n");
        for (int j = 5 ; j < 29 ; j=j+2) {
            for (int i = 1 ; i < 7 ; i++) {
                std::ostringstream left_path, right_path, dst_path;
                left_path << "srcrobot/7cm/left_2.png"; //path fichier gauche entrant
                right_path << "srcrobot/7cm/right_2.png"; //path fichier droite entrant
                dst_path << "dstrobot/7cm/disp" << i << "-sad" << j << ".png"; //path fichier sortant
                std::string left_string = left_path.str();
                std::string right_string = right_path.str();
                std::string dst_string = dst_path.str();

                printf("accessing file %s \n", left_string.c_str());
                printf("accessing file %s \n", right_string.c_str());
                cv::Mat left = cv::imread(left_string);
                cv::Mat right = cv::imread(right_string);
                cv::Mat tmp;
                disp(left, right, &tmp, 16*i, j);
                cv::Mat result;
                cv::bitwise_not(tmp, result);

                cv::imwrite(dst_string, result);
            }
        }
    }
}
