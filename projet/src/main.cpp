#include "headers/mainwindow.h"
#include "headers/include.h"
#include <QApplication>

int main(int argc, char *argv[])
{


    if (argc == 1)
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    }

    if (argc == 3)
    {
    //param
    cv::Mat left = cv::imread(argv[1]);
    cv::Mat right = cv::imread(argv[2]);

    cv::Mat result;

    dispMap(left, right, &result);

    cv::imwrite("filename.jpg", result); //incrémenter le nom du fichier
    //automatiser les SS sur Unity.
    return 0;
    }

}
