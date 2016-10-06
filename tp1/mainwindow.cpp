/*#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    QLabel *imagedisplay = new QLabel(this);
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
    actionCrop = new QAction(tr("&Crop"),this);
    connect(actionCrop, SIGNAL(triggered()), this, SLOT(openNewWindow()));
}

void MainWindow::createMenus()
{
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    QMenu *menu = menuBar()->addMenu(tr("&About"));
    QMenu *menuEdit = menuBar()->addMenu(tr("&Edit"));
    menu->addAction(actionAbout);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionQuit);
    menuEdit->addAction(actionCrop);
}

void MainWindow::about()
{
    QMessageBox::information(this, "About", "Bonjour, ceci est un about random.");
}

void MainWindow::open() //Image charge pas, mais si le code est mis dans le constructeur de main window ca marche. Segmentation fault au niveau de imagedisplay->setpixmap
{
    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir image ..."),"",tr("Image (*.png)"));
    //QFileInfo fileInfo(file);
    //chemin = fileInfo.path() + fileInfo.fileName();
    //QMessageBox::information(this,"Open File", "Ceci est le chemin specifie:"+ chemin);
    QImageReader reader(file);
    QImage image = reader.read();
    QPixmap pixelmap = QPixmap::fromImage(image);

    //imagedisplay->setPixmap(QPixmap::fromImage(imageObject));  //les 2 lignes font crasher quand on ouvre un fichier.
    //imagedisplay->adjustSize();

}

void MainWindow::openNewWindow() //Ouvre une nouvelle fentre, mais pas encore parametre pour gerer une image crop en 2.
{
   QWindow *mMyNewWindow = new QWindow();
   mMyNewWindow->show();
   QLabel *imagedisplay1 = new QLabel(this);
   QImageReader reader("Pictures\15.jpg");
   QImage image1 = reader.read();
   QPixmap pixelmap1 = QPixmap::fromImage(image1);
   imagedisplay1->setPixmap(pixelmap1);
   imagedisplay1->adjustSize();

}
*/

#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    setFixedSize(900,900);
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

    actionCrop = new QAction(tr("&Crop"),this);
    connect(actionCrop, SIGNAL(triggered()), this, SLOT(openNewWindow()));

    actionSplit = new QAction(tr("&Split"),this);
    connect(actionSplit, SIGNAL(triggered()), this, SLOT(split()));

}

void MainWindow::createMenus()
{
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    QMenu *menu = menuBar()->addMenu(tr("&About"));
    QMenu *menuEdit = menuBar()->addMenu(tr("&Edit"));

    menu->addAction(actionAbout);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionQuit);
    menuEdit->addAction(actionCrop);
    menuEdit->addAction(actionSplit);
}

void MainWindow::about()
{
    QMessageBox::information(this, "About", "Bonjour, ceci est un about random.");
}

void MainWindow::open() //Image charge pas, mais si le code est mis dans le constructeur de main window ca marche. Segmentation fault au niveau de imagedisplay->setpixmap
{
    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir image ..."),"",tr("Images (*.jpg *.png)"));
    QFileInfo fileInfo(file);
    chemin = fileInfo.path() + fileInfo.fileName();
    QMessageBox::information(this,"Open File", "Ceci est le chemin specifie:"+ chemin);
    QImageReader reader(file);
    reader.setAutoTransform(true);
    QImage image = reader.read();
    QPixmap pixelmap = QPixmap::fromImage(image);

    QLabel* imagedisplay = new QLabel(this);
    imagedisplay->setFixedSize(this->width(), this->height());


    imagedisplay->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));  //les 2 lignes font crasher quand on ouvre un fichier.
    //imagedisplay->adjustSize();
    imagedisplay->show();
}

void MainWindow::openNewWindow() //Ouvre une nouvelle fentre, mais pas encore parametre pour gerer une image crop en 2.
{
   /*QWindow *mMyNewWindow = new QWindow();
   QWindow *mMyNewWindow1 = new QWindow();
   mMyNewWindow->show();
   mMyNewWindow1->show();
   QLabel *imagedisplay1 = new QLabel(mMyNewWindow);
   QLabel *imagedisplay2 = new QLabel(mMyNewWindow1);
   QImageReader reader("Pictures\15.jpg");
   QImage image = reader.read();
   QPixmap pixelmap = QPixmap::fromImage(image);
   imagedisplay1->setFixedSize(this->width()/2, this->height());
   imagedisplay2->setFixedSize(this->width()/2, this->height());
   imagedisplay1->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
   imagedisplay2->setPixmap((&pixelmap)->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio));
   imagedisplay1->show();
   imagedisplay2->show();*/

   QWindow *mMyNewWindow = new QWindow();
   mMyNewWindow->show();
}

void MainWindow:: openNewWindow(QImage img)
{
    QWindow *mMyNewWindow = new QWindow();
    mMyNewWindow->show();
    QLabel *imagedisplay = new QLabel(mMyNewWindow);
    int width = img.width();
    int height = img.height();
    imagedisplay->setFixedSize(width, height);
    imagedisplay->show();
}

void MainWindow:: split()
{
    int width = imageObject.width();
    int height = imageObject.height();
    QRect rect1(0, 0, width/2, height);
    QRect rect2(width/2, 0, width, height);
    QImage original(imageObject);
    QImage half1 = original.copy(rect1);
    QImage half2 = original.copy(rect2);
    openNewWindow(half1);
    openNewWindow(half2);

}





