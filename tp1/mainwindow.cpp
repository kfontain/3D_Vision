#include "mainwindow.h"
int i=0, j=0;
MainWindow::MainWindow() : QMainWindow()
{
    createActions();
    createMenus();
}

void MainWindow::createActions()
{
    actionAbout = new QAction(tr("&About"),this);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    actionOpen = new QAction(tr("&Open"),this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    actionQuit = new QAction(tr("&Quit"),this);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    actionSplit = new QAction(tr("&Split"),this);
    connect(actionSplit, SIGNAL(triggered()), this, SLOT(split()));
    actionCrop = new QAction(tr("&Crop"),this);
    connect(actionCrop, SIGNAL(triggered()), this, SLOT(crop()));
}

void MainWindow::createMenus()
{
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    QMenu *menu = menuBar()->addMenu(tr("&About"));
    QMenu *menuEdit = menuBar()->addMenu(tr("&Edit"));
    menu->addAction(actionAbout);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionQuit);
    menuEdit->addAction(actionSplit);
    menuEdit->addAction(actionCrop);
}

void MainWindow::about()
{
    QMessageBox::information(this, "About", "Bonjour, ceci est un about random.");
}

void MainWindow::open()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir image ..."),"",tr("Images (*.jpg *.png)"));
    QFileInfo fileInfo(file);
    chemin = fileInfo.path() + fileInfo.fileName();
    QMessageBox::information(this,"Open File", "Ceci est le chemin specifie:"+ chemin);
    QImageReader reader(file);
    imageObject = reader.read();
    pixelmap = QPixmap::fromImage(imageObject);

    imagedisplay = new QLabel(this);
    imagedisplay->setGeometry(QRect(0, 25, this->width(), this->height()-25));
    imagedisplay->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
    imagedisplay->show();
    i=1;
}

void MainWindow::resizeEvent(QResizeEvent *event){
    if(i==1){
    imagedisplay->setFixedSize(event->size());
    imagedisplay->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
    }
}


// TP 2

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int p1x =(e->x()/this->width()*pixelmap.width());
    int p1y =((e->y()-25)/(this->height()-25)*pixelmap.height());
    point1.setX(p1x);
    point1.setY(p1y);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    int p2x =(e->x()/this->width()*pixelmap.width());
    int p2y =((e->y()-25)/(this->height()-25)*pixelmap.height());
    point2.setX(p2x);
    point2.setY(p2y);

    if(j==1){

        QRect rect (point1, point2);
        QPixmap pixelmap2 = pixelmap.copy(rect);
        imagedisplay->setPixmap((&pixelmap2)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
        imagedisplay->adjustSize();
    }
}

void MainWindow:: crop()
{
    j=1;
}

void MainWindow:: split()
{
    int width = imageObject.width();
    int height = imageObject.height();
    QRect rect1(0, 0, width/2, height);
    QRect rect2(width/2, 0, width/2, height);
    QImage original(imageObject);
    QImage half1 = original.copy(rect1);
    QImage half2 = original.copy(rect2);
    openNewWindow(half1);
    openNewWindow(half2);
}


void MainWindow:: openNewWindow(QImage img)
{
    QWidget* mMyNewWindow = new QWidget();
    QLabel *imagedisplay1 = new QLabel(mMyNewWindow);

    QPixmap pixelmap1 = QPixmap::fromImage(img);

    int width = img.width();
    int height = img.height();

    imagedisplay1->setFixedSize(width, height);

    imagedisplay1->setPixmap(pixelmap1);

    imagedisplay1->show();
    mMyNewWindow->show();
}




