#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    setFixedSize(230,150);

    bouton = new QPushButton("About", this);
    bouton->move(50,50);

    createActions();
    createMenus();
}

void MainWindow::createActions()
{
    actionAbout = new QAction(tr("&About"),this);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    QMenu *menu = menuBar()->addMenu(tr("&About"));
    menu->addAction(actionAbout);
}

void MainWindow::about()
{
    QMessageBox::information(this, "About", "Bonjour, ceci est un about de merde.");
}
