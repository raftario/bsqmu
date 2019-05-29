#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setSaveScores(int);
    void setSaveSettings(int);
    void setBackupApk(int);
    void selectSongsFolder();

private:
    Ui::MainWindow *ui;
    bool saveScores;
    bool saveSettings;
    bool backupApk;
    std::string songsfolderPath;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    std::string adbPath;
#endif
};

#endif // MAINWINDOW_H
