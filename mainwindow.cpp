#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    if (ui->plainTextEdit->document()->isModified())
    {
        switch(
        QMessageBox::question(this,
                              tr("File modified"),
                              tr("You modified the contents of the currently oppened file. Save current file?"),
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                              QMessageBox::Cancel)
               )
        {
        case QMessageBox::Yes:
            this->saveFileAs();
            break;

        case QMessageBox::Cancel:
            return;

        default:
        case QMessageBox::No:
            break;
        }
    }

    ui->plainTextEdit->setPlainText("");
    ui->plainTextEdit->setDocumentTitle("");
    this->setWindowTitle("Notepad - New file");

    return;
}

void MainWindow::doOperationFile(QString fileName, QIODevice::OpenModeFlag flag, QString errorTitle, QString errorMessage)
{
    QFile file(fileName);

    if (!file.open(flag))
    {
        QMessageBox::critical(this, tr(errorTitle.toStdString().c_str()), tr(errorMessage.toStdString().c_str()));
        return;
    }

    QTextStream stream(&file);

    ui->plainTextEdit->document()->setModified(false);
    ui->plainTextEdit->setDocumentTitle(fileName);
    this->setWindowTitle("Notepad - " + ui->plainTextEdit->documentTitle());

    if (flag == QIODevice::ReadOnly)
    {
        ui->plainTextEdit->document()->setPlainText(stream.readAll());
        file.close();
        return;
    }

    stream << ui->plainTextEdit->document()->toPlainText();
    file.close();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "")
        doOperationFile(fileName, QIODevice::ReadOnly, "Error", "Could not open file");
}

void MainWindow::saveFile()
{
    QString fileName = ui->plainTextEdit->documentTitle();

    if (fileName == "")
    {
        this->saveFileAs();
        return;
    }

    doOperationFile(fileName, QIODevice::WriteOnly, "Error", "Could not save file");
}

void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "")
        doOperationFile(fileName, QIODevice::WriteOnly, "Error", "Could not save file");
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::about()
{
    QMessageBox::information(this, "About", "Developed by Renan");
}
