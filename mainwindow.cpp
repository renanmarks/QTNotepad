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

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->plainTextEdit->document()->setPlainText(in.readAll());
        ui->plainTextEdit->setDocumentTitle(fileName);
        this->setWindowTitle("Notepad - " + ui->plainTextEdit->documentTitle());
        file.close();
    }
}

void MainWindow::saveFile()
{
    QString fileName = ui->plainTextEdit->documentTitle();

    if (fileName == "")
    {
        this->saveFileAs();
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Could save file"));
        return;
    }
    QTextStream out(&file);
    out << ui->plainTextEdit->document()->toPlainText();
    file.close();

    ui->plainTextEdit->document()->setModified(false);
}

void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could save file"));
            return;
        }
        QTextStream out(&file);
        out << ui->plainTextEdit->document()->toPlainText();
        file.close();

        ui->plainTextEdit->document()->setModified(false);
        ui->plainTextEdit->setDocumentTitle(fileName);
        this->setWindowTitle("Notepad - " + ui->plainTextEdit->documentTitle());
    }
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::about()
{
    QMessageBox::information(this, "About", "Developed by Helix");
}
