#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agreementdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    AgreementDialog ad;
    if (ad.exec() == 0) {
        exit(EXIT_SUCCESS);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
