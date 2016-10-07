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
#include <QResizeEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QString chemin;

private:
    void createMenus();
    void createActions();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void resizeEvent ( QResizeEvent * event );
    void openNewWindow(QImage img);

private slots:
    void about();
    void open();
    void split();
    void crop();

private:
    QAction* actionAbout;
    QAction* actionOpen;
    QAction* actionQuit;
    QAction* actionSplit;
    QAction* actionCrop;
    QImage imageObject;
  //  QWindow* mMyNewWindow;
    QLabel* imagedisplay;
    QPixmap pixelmap;
    QPoint point1;
    QPoint point2;
};

#endif // MAINWINDOW_H
