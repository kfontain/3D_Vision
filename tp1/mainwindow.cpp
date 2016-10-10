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

