#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include "booksmain.h"
#include "readersmain.h"
#include "borrowingwindow.h"
#include "databasehandler.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void openBooksWindow();
    void openReadersWindow();
    void enableButtons();
    void openBorrowWindow();
    void endBorrow();
    void updateList();
    void extendBorrow();
};
#endif // MAINWINDOW_H
