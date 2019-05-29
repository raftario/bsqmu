#include <cstdlib>
#include <QMessageBox>
#include <QFileDialog>
#include <ostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agreementdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    saveScores = true;
    saveSettings = true;
    backupApk = true;
    songsfolderPath = "";
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    adbPath = "";
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    const auto deps = new int(std::system("where java"));
#else
    const auto deps = new int(std::system("which dotnet adb java"));
#endif
    if (*deps != 0) {
        auto dd = new QMessageBox(this);
        dd->setWindowTitle("Missing Dependencies");
        dd->setIcon(QMessageBox::Critical);
        dd->setText("It appears you are missing required dependencies. Make sure they are installed and that you launched the program from a CLI with a correct PATH.");
        dd->exec();
        exit(EXIT_FAILURE);
    } else {
        delete deps;
    }

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    auto adbPathInput = new QFileDialog(this);
    adbPathInput->setNameFilter("adb Executable (adb.exe)");
    adbPathInput->setFileMode(QFileDialog::ExistingFile);
    adbPathInput->exec();
    adbPath = adbPathInput->selectedUrls.first()->toString().toStdString();
    if (adbPath == "") {
        exit(EXIT_FAILURE);
    } else {
        delete adbPathInput;
        cout << adbPath;
    }
#endif

    auto ad = new AgreementDialog(this);
    if (ad->exec() == 0) {
        exit(EXIT_SUCCESS);
    } else {
        delete ad;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
