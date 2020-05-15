#ifndef WINDOWFILE_H
#define WINDOWFILE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include "dialogsize.h"
#include "threaddataform.h"
#include <QLabel>
#include <QFontDialog>

namespace Ui {
class windowFile;
}

class windowFile : public QMainWindow
{
    Q_OBJECT
public:
    explicit windowFile(QWidget *parent = nullptr);
    ~windowFile();
    void openFile();
    void openFileByName(QString);
    void output(QString);
    void createFile();
    void createFileStandard();
    void createFileFinish(QString);
    void saveFile();
    void saveFileLast();
    void deleteFile();
    void newFile();
    void fontChange();
private:
    Ui::windowFile *ui;
    QLabel * label = NULL;
    void iniSignol();
    threadDataForm threadA;
};

#endif // WINDOWFILE_H
