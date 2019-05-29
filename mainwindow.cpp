#include <cstdlib>
#include <QMessageBox>
#include <QFileDialog>
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
    auto adbd = new QMessageBox(this);
    adbd->setWindowTitle("adb");
    adbd->setIcon(QMessageBox::Question);
    adbd->setText("Please select the adb.exe file to use for the process.");
    adbd->exec();
    delete adbd;

    auto adbPathInput = new QFileDialog(this);
    adbPathInput->setNameFilter("adb Executable (adb.exe)");
    adbPathInput->setFileMode(QFileDialog::ExistingFile);
    adbPathInput->exec();
    if (adbPathInput->selectedUrls().isEmpty()) {
        exit(EXIT_FAILURE);
    }
    adbPath = adbPathInput->selectedUrls().first().path().toStdString();
    delete adbPathInput;
#endif

    auto ad = new AgreementDialog(this);
    if (ad->exec() == 0) {
        exit(EXIT_SUCCESS);
    } else {
        delete ad;
    }

    QObject::connect(ui->scoresCheckbox, SIGNAL(stateChanged(int)), this, SLOT(setSaveScores(int)));
    QObject::connect(ui->settingsCheckbox, SIGNAL(stateChanged(int)), this, SLOT(setSaveSettings(int)));
    QObject::connect(ui->backupCheckbox, SIGNAL(stateChanged(int)), this, SLOT(setBackupApk(int)));
    QObject::connect(ui->browseButton, SIGNAL(released()), this, SLOT(selectSongsFolder()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSaveScores(int checkState) {
    if (checkState == Qt::Unchecked) {
        saveScores = false;
    } else {
        saveScores = true;
    }
}

void MainWindow::setSaveSettings(int checkState) {
    if (checkState == Qt::Unchecked) {
        saveSettings = false;
    } else {
        saveSettings = true;
    }
}

void MainWindow::setBackupApk(int checkState) {
    if (checkState == Qt::Unchecked) {
        backupApk = false;
    } else {
        backupApk = true;
    }
}

void MainWindow::selectSongsFolder() {
    auto sfpi = new QFileDialog(this);
    sfpi->setOption(QFileDialog::ShowDirsOnly, true);
    sfpi->setFileMode(QFileDialog::Directory);
    sfpi->exec();
    if (sfpi->selectedUrls().isEmpty()) {
        songsfolderPath = "";
        ui->patchButton->setEnabled(false);
    } else {
        songsfolderPath = sfpi->selectedUrls().first().path().toStdString();
        ui->patchButton->setEnabled(true);
    }
    delete sfpi;

    ui->songfolderPath->setText(QString::fromStdString(songsfolderPath));
}
