#include "mainwindow.h"

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
