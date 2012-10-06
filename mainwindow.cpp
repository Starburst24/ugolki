#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	piece of googlecode yepS
	2222

}

MainWindow::~MainWindow()
{

    delete ui;
}
