#include "headers/mainwindow.h"
#include "headers/include.h"
#include <QApplication>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{


    if (argc == 1) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    }

    if (argc == 2) {

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

}
