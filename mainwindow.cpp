#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *books=MainWindow::findChild<QPushButton*>("booksButton");
    connect(books, SIGNAL(released()),this,SLOT(openBooksWindow()));

    QPushButton *readers=MainWindow::findChild<QPushButton*>("readersButton");
    connect(readers, SIGNAL(released()),this,SLOT(openReadersWindow()));

    QPushButton *borrow=MainWindow::findChild<QPushButton*>("borrowButton");
    connect(borrow, SIGNAL(released()),this,SLOT(openBorrowWindow()));

    QPushButton *endBorrow=MainWindow::findChild<QPushButton*>("endBorrow");
    connect(endBorrow, SIGNAL(released()),this,SLOT(endBorrow()));

    QPushButton *extendBorrow=MainWindow::findChild<QPushButton*>("extendBorrow");
    connect(extendBorrow, SIGNAL(released()),this,SLOT(extendBorrow()));

    QCheckBox *returned=MainWindow::findChild<QCheckBox*>("showReturnedCheckBox");
    connect(returned, SIGNAL(released()),this,SLOT(updateList()));

    updateList();
}

MainWindow::~MainWindow()
{
    delete ui;
    return;
}

void MainWindow::openBooksWindow()
{
    this->setEnabled(false);
    BooksMain window;
    window.show();
    window.exec();
    this->setEnabled(true);
}

void MainWindow::openReadersWindow()
{
    this->setEnabled(false);
    ReadersMain window;
    window.show();
    window.exec();
    this->setEnabled(true);
}

void MainWindow::updateList()
{
    QCheckBox *returned=MainWindow::findChild<QCheckBox*>("showReturnedCheckBox");
    QLabel *listLabel=MainWindow::findChild<QLabel*>("label");

    extern databaseHandler db;
    QStringListModel *model;
    model = new QStringListModel(this);

    if(returned->isChecked())
    {
        model->setStringList(db.getAllBorrowings());
        listLabel->setText("Wszystkie wypożyczenia");
    }
    else
    {
        model->setStringList(db.getBorrowings());
        listLabel->setText("Aktywne wypożyczenia");
    }
    QListView *lv=MainWindow::findChild<QListView*>("listView");
    lv->setModel(model);
    lv->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                            QAbstractItemView::DoubleClicked);
    connect(lv->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(enableButtons()));
}

void MainWindow::endBorrow()
{
    extern databaseHandler db;
    QListView *lv=MainWindow::findChild<QListView*>("listView");
    QModelIndex index=lv->currentIndex();
    qDebug()<<index.data(Qt::DisplayRole).toString();
    QString id=index.data(Qt::DisplayRole).toString();

    for(int i=0;i<id.length();i++)
    {
        if(id[i]=='.')
        {

            id.chop(id.length()-i);
            qDebug()<<"id to END"<<id.toInt();
            db.endBorrow(id.toInt());
            break;
        }
    }
    updateList();
}

void MainWindow::extendBorrow()
{
    this->setEnabled(false);

    extern databaseHandler db;

    QListView *lv=MainWindow::findChild<QListView*>("listView");
    QModelIndex index=lv->currentIndex();
    qDebug()<<index.data(Qt::DisplayRole).toString();
    QString id=index.data(Qt::DisplayRole).toString();

    for(int i=0;i<id.length();i++)
    {
        if(id[i]=='.')
        {

            id.chop(id.length()-i);
            qDebug()<<"id to END"<<id.toInt();
            break;
        }
    }
    borrowingWindow borrowing;
    borrowing.setId(id.toInt());
    borrowing.show();
    borrowing.exec();
    updateList();
    this->setEnabled(true);
}

void MainWindow::enableButtons()
{
    MainWindow::findChild<QPushButton*>("endBorrow")->setEnabled(true);
    MainWindow::findChild<QPushButton*>("extendBorrow")->setEnabled(true);
}

void MainWindow::openBorrowWindow()
{
    this->setEnabled(false);
    borrowingWindow borrowing;
    borrowing.setId(0);
    borrowing.show();
    borrowing.exec();
    updateList();
    this->setEnabled(true);
}
