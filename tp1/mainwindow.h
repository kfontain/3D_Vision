#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QWidget>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void createMenus();
    void createActions();

private slots:
    void about();

private:
    QPushButton *bouton;
    QAction *actionAbout;
};

#endif // MAINWINDOW_H
