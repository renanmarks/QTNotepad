#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void quit();
    void about();
    
private:
    Ui::MainWindow* ui;

    void doOperationFile(QString, QIODevice::OpenModeFlag, QString, QString);
};

#endif // MAINWINDOW_H
