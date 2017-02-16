#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"
#include "convert.h"
#include "edit.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString filepath;

private:
    void createMenus();
    void createActions();
    void openNewWindow(QImage img);


    QPixmap pixelmap;
    QLabel *imagedisplay;
    QImage imageObject;

    QAction *actionOpen;
    QAction *actionConvertTest;
    QAction *actionSplitTest;
    QAction *actionSobelTest;
    QAction *actionSurfTest;
    QAction *actionSurfMatchTest;
    QAction *actionDispMapTest;
    QAction *actionDispMapInvertTest;
    QAction *actionDepthMapTest;
    QAction *actionRobotTest;


private slots:
    void openFile();
    void convertTest();
    void splitTest();
    void sobelTest();
    void surfTest();
    void surfMatchTest();
    void dispMapTest();
    void dispMapInvertTest();
    void depthMapTest();
    void robotTest();

};

#endif // MAINWINDOW_H
