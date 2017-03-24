#include "headers/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    setWindowTitle("Projet Vision Robotique 3D");
}

MainWindow::~MainWindow()
{

}

///Permet l'ouverture d'un fichier image et de l'afficher dans la fenêtre principale.
void MainWindow::openFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir image ..."),"",tr("Images (*.jpg *.png)"));
    QFileInfo fileInfo(file);
    filepath = fileInfo.path() + fileInfo.fileName();
    QImageReader reader(file);
    imageObject = reader.read();
    pixelmap = QPixmap::fromImage(imageObject);
    int newheight = pixelmap.height();
    int newwidth = pixelmap.width();
    this->setFixedSize(newwidth, newheight);

    imagedisplay = new QLabel(this);
    imagedisplay->setGeometry(QRect(0, 25, this->width(), this->height()-25));
    imagedisplay->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
    imagedisplay->show();
}

///Initialise les menus de la fenêtre principale.
void MainWindow::createMenus()
{
    QMenu *menuFile = menuBar()->addMenu(tr("File"));
    menuFile->addAction(actionOpen);

    QMenu *menuEdit = menuBar()->addMenu(tr("Edit"));
    menuEdit->addAction(actionConvertTest);
    menuEdit->addAction(actionSplitTest);
    menuEdit->addAction(actionSobelTest);
    menuEdit->addAction(actionSurfTest);
    menuEdit->addAction(actionSurfMatchTest);
    menuEdit->addAction(actionDispMapTest);
    menuEdit->addAction(actionDispMapInvertTest);
    menuEdit->addAction(actionDepthMapTest);
    menuEdit->addAction(actionSGBM);

}

///Initialise les actions contenues dans les menus de la fenêtre principale.
void MainWindow::createActions()
{
    actionOpen = new QAction(tr("Open File"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    actionConvertTest = new QAction(tr("Convert QImage to CV::Mat"), this);
    connect(actionConvertTest, SIGNAL(triggered()), this, SLOT(convertTest()));
    actionSplitTest = new QAction(tr("Split test"), this);
    connect(actionSplitTest, SIGNAL(triggered()), this, SLOT(splitTest()));
    actionSobelTest = new QAction(tr("Sobel test"), this);
    connect(actionSobelTest, SIGNAL(triggered()), this, SLOT(sobelTest()));
    actionSurfTest = new QAction(tr("Surf test"), this);
    connect(actionSurfTest, SIGNAL(triggered()), this, SLOT(surfTest()));
    actionSurfMatchTest = new QAction(tr("Surf Match test"), this);
    connect(actionSurfMatchTest, SIGNAL(triggered()), this, SLOT(surfMatchTest()));
    actionDispMapTest = new QAction(tr("Disp Map test"), this);
    connect(actionDispMapTest, SIGNAL(triggered()), this, SLOT(dispMapTest()));
    actionDispMapInvertTest = new QAction(tr("Disp Map + Invert test"), this);
    connect(actionDispMapInvertTest, SIGNAL(triggered()), this, SLOT(dispMapInvertTest()));
    actionDepthMapTest = new QAction(tr("Depth Map test"), this);
    connect(actionDepthMapTest, SIGNAL(triggered()), this, SLOT(depthMapTest()));
    actionSGBM = new QAction(tr("SGBM test"), this);
    connect(actionSGBM, SIGNAL(triggered()), this, SLOT(SGBMtest()));

}



///Ouvre une nouvelle fenêtre avec comme image celle entrée en paramètre.

void MainWindow:: openNewWindow(QImage img)
{
    QWidget *mMyNewWindow = new QWidget();
    QLabel *imagedisplay = new QLabel(mMyNewWindow);

    QPixmap pixelmap1 = QPixmap::fromImage(img);

    int width = img.width();
    int height = img.height();

    imagedisplay->setFixedSize(width, height);

    imagedisplay->setPixmap(pixelmap1);

    imagedisplay->show();
    mMyNewWindow->show();

}

///Slot de test pour la fonction convert.
void MainWindow::convertTest()
{
    cv::Mat mat;
    mat = qImage2Mat(imageObject, false);
    QImage img;
    img = mat2QImage(mat, false);
    openNewWindow(img);
}

///Slot de test pour la fonction split.
void MainWindow::splitTest()
{
    cv::Mat matLeft, matRight;
    split(imageObject, &matLeft, &matRight);
    QImage left, right;
    left = mat2QImage(matLeft, true);
    right = mat2QImage(matRight, true);
    openNewWindow(left);
    openNewWindow(right);
}

///Slot de test pour la fonction détectant les bords (utilisant Sobel)
void MainWindow::sobelTest()
{
    QImage result;
    cv::Mat tmp = qImage2Mat(imageObject, true);
    cv::Mat tmp2;
    sobel(tmp, &tmp2);
    result = mat2QImage(tmp2, true);
    openNewWindow(result);
}

///Slot de test pour la fonction Surf
void MainWindow::surfTest()
{
    cv::Mat src = qImage2Mat(imageObject, true);
    cv::Mat tmp;
    surf(src, &tmp);

    QImage result = mat2QImage(tmp, true);
    openNewWindow(result);
}

///Slot de test pour la fonction SurfMatch
void MainWindow::surfMatchTest()
{
    cv::Mat left, right;
    split(imageObject, &left, &right);
    cv::Mat tmp;
    surfMatch(left, right, &tmp);

    QImage result;
    result = mat2QImage(tmp, true);

    openNewWindow(result);
}

///Slot de test pour la fonction dispMap
void MainWindow::dispMapTest()
{
    cv::Mat left, right;
    split(imageObject, &left, &right);
    cv::Mat tmp;
    dispMap(left, right, &tmp);

    QImage result;
    result = mat2QImage(tmp, true);

    openNewWindow(result);
}

///Slot de test pour la fonction dispMap + inversion des couleurs
void MainWindow::dispMapInvertTest()
{
    cv::Mat left, right;
    split(imageObject, &left, &right);
    cv::Mat tmp;
    dispMap(left, right, &tmp);

    cv::Mat tmp2;
    //Applique un NON logique à chaque bit => Inverse les couleurs
    cv::bitwise_not(tmp,tmp2);

    QImage result;
    result = mat2QImage(tmp2, true);

    openNewWindow(result);
}

void MainWindow::depthMapTest()
{
    cv::Mat left, right;
    split(imageObject, &left, &right);
    cv::Mat tmp, tmp2;
    dispMap(left, right, &tmp);

    //Applique un NON logique à chaque bit => Inverse les couleurs
    cv::bitwise_not(tmp,tmp2);

    cv::Mat depth;
    depthMap(tmp2, &depth);

    QImage result;
    result = mat2QImage(depth, true);

    openNewWindow(result);
}

void MainWindow::SGBMtest()
{
    dispSGBM();
}

//EcartCamera * DistFocale / mapDisp(y,x)
