#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QImageReader>
#include <QPixmap>
#include <QResizeEvent>
#include <QRubberBand>
#include <QToolTip>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"


/*regles definitions variables:
 * tout minuscules = variables temporaires dans la fonctions (ex: newheight)
 * minuscule puis majuscule a chaque debut de mot = variables/fonctions definies dans le .h et globales (ex: actionAbout)
 * majuscules a chaque mot = class (ex: MainWindow)
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QString chemin;

private:
    void createMenus();
    void createActions();
    void resizeEvent ( QResizeEvent * event );
    void openNewWindow(QImage img);
    void openNewWindow(cv::Mat img, const char* name);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void createStatusBar();
    cv::Mat QImage2Mat(QImage *src);
    QImage mat2QImage(cv::Mat src);
    cv::Mat blur(cv::Mat src);

private slots:
    void about();
    void open();
    void split();
    void crop();
    void convert_test(); //QImage to CV::Mat
    void convert_test2(); //CV::Mat to QImage
    void blur();
    void sobel();
    void canny();

private:
    QAction *actionAbout;
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionSplit;
    QAction *actionCrop;
    QAction *actionConvertTest; //QImage to CV::Mat
    QAction *actionBlur;
    QAction *actionConvertTest2; //CV::Mat to QImage
    QAction *actionDifference;
    QAction *actionSobel;
    QAction *actionCanny;
    QImage imageObject;
    QWindow *mMyNewWindow;
    QLabel *imagedisplay;
    QPixmap pixelmap;
    QPoint point1;
    QPoint point2;
    QPoint originCrop;
    QPoint endCrop;
    QRubberBand *rubberBand;
    bool cropActive;
    bool imageOpen;

};

#endif // MAINWINDOW_H
