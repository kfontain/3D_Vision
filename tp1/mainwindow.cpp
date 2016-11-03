#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    createActions();
    createMenus();
    createStatusBar();
    imageOpen=false;
    cropActive=false;
    setWindowTitle("Projet Vision Robotique 3D");
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
    actionConvertTest = new QAction(tr("&Convert QImage to CV::Mat"),this);
    connect(actionConvertTest, SIGNAL(triggered()), this, SLOT(convert_test()));
    actionConvertTest2 = new QAction(tr("&Convert CV::Mat to QImage"),this);
    connect(actionConvertTest2, SIGNAL(triggered()), this, SLOT(convert_test2()));
    actionBlur = new QAction(tr("&Blur"),this);
    connect(actionBlur, SIGNAL(triggered()), this, SLOT(blur()));
    actionSobel = new QAction(tr("&Sobel"),this);
    connect(actionSobel, SIGNAL(triggered()), this, SLOT(sobel()));
    actionCanny = new QAction(tr("&Canny (non fonctionnel)"), this);
    connect(actionCanny, SIGNAL(triggered()), this, SLOT(canny()));

}

void MainWindow::createMenus()
{
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    QMenu *menu = menuBar()->addMenu(tr("&About"));
    QMenu *menuEdit = menuBar()->addMenu(tr("&Edit"));
    QMenu *menuTP3 = menuBar()->addMenu(tr("tp3"));
    menu->addAction(actionAbout);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionQuit);
    menuEdit->addAction(actionSplit);
    menuEdit->addAction(actionCrop);
    menuTP3->addAction(actionConvertTest);
    menuTP3->addAction(actionBlur);
    menuTP3->addAction(actionConvertTest2);
    menuTP3->addAction(actionSobel);
    menuTP3->addAction(actionCanny);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
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
    int newheight = pixelmap.height();                     //Met la mainwindow a la taille de l'image ouverte
    int newwidth = pixelmap.width();
    this->setFixedSize(newwidth, newheight);

    imagedisplay = new QLabel(this);
    imagedisplay->setGeometry(QRect(0, 25, this->width(), this->height()-25));
    imagedisplay->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
    imagedisplay->show();
    imageOpen=true;


}

void MainWindow::resizeEvent(QResizeEvent *event){
    if(imageOpen){
    imagedisplay->setFixedSize(event->size());
    imagedisplay->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
    }
}



void MainWindow:: crop()
{
    cropActive=true;
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


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    originCrop = event->pos();  //Point de depart du crop et du poisitionnement du rectangle de selection

    rubberBand = new QRubberBand(QRubberBand::Rectangle, this); //rectangle de selection
    rubberBand->setGeometry(QRect(originCrop, QSize()));
    rubberBand->show();
    statusBar()->showMessage(tr("Ready to Crop" ));
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(originCrop, event->pos()).normalized()); //Permet de faire evoluer le rectangle de selection en bougeant la souris
    QToolTip::showText( event->globalPos(), QString("%1,%2")
                                                 .arg(rubberBand->size().width())
                                                 .arg(rubberBand->size().height()),this );
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    rubberBand->hide(); //Cache le rectangle de selection quand on lache la souris
    endCrop = event->pos(); //Coordonnées du dernier point quand on lache la souris
    if(endCrop.x()>pixelmap.width()){ //Mesures de securitées pour le crop dans le cas ou on sort de la fenetre, je sais pas si c'est necessaire.
        endCrop.setX(pixelmap.width()); //Une solution optimale serait de limiter le mouvement de la souris a la fenetre
    }
    if(endCrop.y()>pixelmap.height()){
        endCrop.setY(pixelmap.height());
    }


    if(cropActive){

        QRect rect (originCrop, endCrop);
        QPixmap pixelmap2 = pixelmap.copy(rect);
        pixelmap= pixelmap2;
        imagedisplay->setPixmap((&pixelmap2)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));

    }
    cropActive=false;
}

//TP3

cv::Mat MainWindow::QImage2Mat(QImage *src)
{
    cv::Mat tmp(src->height(),src->width(),CV_8UC4,(uchar*)src->bits(),src->bytesPerLine());
    cv::Mat result = cv::Mat(tmp.rows, tmp.cols, CV_8UC3 );
    int from_to[] = { 0,0,  1,1,  2,2 };
    cv::mixChannels( &tmp, 1, &result, 1, from_to, 3 );

    return result;
}

void MainWindow::openNewWindow(cv::Mat img, const char* name)
{
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE );
    cv::imshow(name, img );

    cv::waitKey(0);
}

void MainWindow::convert_test()
{
    cv::Mat tmp;
    tmp = QImage2Mat(&imageObject);
    openNewWindow(tmp, "Convert Test");
}

cv::Mat MainWindow::blur(cv::Mat src)
{
    cv::Mat result;

    int kernel_size = 31;
    for (int i = 1; i < kernel_size; i = i + 2)
    {
        cv::blur (src, result, cv::Size(i, i), cv::Point(-1,-1));
    }

    return result;
}

void MainWindow::blur()
{
    cv::Mat tmp, result;
    tmp = QImage2Mat(&imageObject);
    result = blur(tmp);

    openNewWindow(result, "OpenCV - Blur");
}

QImage MainWindow::mat2QImage(cv::Mat src)
{
    cv::Mat tmp;
    //Les couleurs n'étant pas stockées de la même façon, une conversion est nécessaire.
    cv::cvtColor(src, tmp, CV_BGR2RGB);
    QImage result;
    result = QImage((const unsigned char*)(tmp.data), tmp.cols, tmp.rows, QImage::Format_RGB888);
    return result;
}

void MainWindow::convert_test2()
{
    cv::Mat src;
    src = QImage2Mat(&imageObject);

    cv::Mat tmp;
    tmp = blur(src);

    QImage result;
    result = mat2QImage(tmp);
    openNewWindow(result);
}

void MainWindow::sobel() //Cette méthode permet de faire resortir les bords d'une image.
{
    cv::Mat src;
    src = QImage2Mat(&imageObject);

    //Convertie l'image source en niveau de gris.
    cv::Mat src_gray;
    cv::cvtColor(src, src_gray, CV_BGR2GRAY);

    //Déclaration des variables nécessaires à l'utilisation de la fonction Sobel.
    cv::Mat x, y;
    int scale = 1;
    int delta = 0;
    int depth = CV_16S;
    int kernel_size = 3;
    int border = cv::BORDER_DEFAULT;

    //La méthode Sobel calcule l'intensité relative d'un pixel à ses voisins.
    //src_gray est l'image source en niveau de gris, x et y sont les cv::Mat recevant le résultat.
    cv::Sobel(src_gray, x, depth, 1, 0, kernel_size, scale, delta, border);
    cv::Sobel(src_gray, y, depth, 0, 1, kernel_size, scale, delta, border);

    //Conversion en CV_8U. 8 bits non signés/pixel, format standard.
    //dx et dy sont les cv::Mat recevant le résultat de chaque appel.
    cv::Mat dx, dy;
    cv::convertScaleAbs(x, dx);
    cv::convertScaleAbs(y, dy);

    //addWeighted permet de faire une moyenne entre dx et dy.
    //0.5 et 0.5 sont les coefficients respectifs appliqués à dx et dy.
    //0 est un scalaire qui peut être ajouté (ici non utilisé).
    cv::Mat result;
    cv::addWeighted(dx, 0.5, dy, 0.5, 0, result);

    openNewWindow(result, "OpenCV - Sobel");
}

void MainWindow::canny()
{
    //Compliqué à faire du à la présence d'une variable globale ?
    /*char* name = "OpenCV - Canny";

    cv::Mat src;
    src = QImage2Mat(&imageObject);

    //Convertie l'image source en niveau de gris et la stocke dans src_gray.
    cv::Mat src_gray;
    src_gray.create(src.size(), src.type());
    cv::cvtColor(src, src_gray, CV_BGR2GRAY);

    cv::namedWindow(name, CV_WINDOW_AUTOSIZE);

    int lowThreshold;
    const int max_lowThreshold = 100;

    cv::createTrackbar("Seuil minimum :", name, &lowThreshold, max_lowThreshold, CannyThreshold);
    */
}
