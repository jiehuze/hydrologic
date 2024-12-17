#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ylogger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ylog.info("MainWindow is an info log");
    ylog.warn("MainWindow is a warning log");
    ylog.error("MainWindow is an error log");

}

MainWindow::~MainWindow()
{
    delete ui;
}
