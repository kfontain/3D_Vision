#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QImageReader>
#include <QPixmap>
#include <QWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QString chemin;

private:
    void createMenus();
    void createActions();

private slots:
    void about();
    void open();
    void openNewWindow();
    void openNewWindow(QImage img);
    void split();

private:
    QAction *actionAbout;
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionCrop;
    QAction *actionSplit;
    QLabel *imagedisplay;
    QImage imageObject;
    QWindow *mMyNewWindow;
    QPixmap *pixelmap;
};

#endif // MAINWINDOW_H
