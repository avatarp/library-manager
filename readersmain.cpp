#include "readersmain.h"
#include "ui_readersmain.h"

ReadersMain::ReadersMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadersMain)
{
    ui->setupUi(this);

    QPushButton *addBook=ReadersMain::findChild<QPushButton*>("addButton");
    connect(addBook, SIGNAL(released()),this,SLOT(addReaderWindow()));

    QPushButton *editBook=ReadersMain::findChild<QPushButton*>("editButton");
    connect(editBook, SIGNAL(released()),this,SLOT(editReaderWindow()));

    QPushButton *closeButton=ReadersMain::findChild<QPushButton*>("closeButton");
    connect(closeButton, SIGNAL(released()),this,SLOT(close()));

    QPushButton *deleteButton=ReadersMain::findChild<QPushButton*>("deleteButton");
    connect(deleteButton, SIGNAL(released()),this,SLOT(deleteReader()));

    updateList();
}

ReadersMain::~ReadersMain()
{
    delete ui;
}


void ReadersMain::addReaderWindow()
{
    this->setDisabled(true);
    readerWindow.setReaderId(0);
    readerWindow.show();
    readerWindow.exec();
    updateList();
    this->setDisabled(false);
}

void ReadersMain::updateList()
{
    extern databaseHandler db;
    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList list;
    list<< "A"<<"B"<<"C"<<"D";
    model->setStringList(db.getReaders());
    QListView *lv=ReadersMain::findChild<QListView*>("listView");
    lv->setModel(model);
    lv->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                            QAbstractItemView::DoubleClicked);
    connect(lv->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(enableButtons()));
}

void ReadersMain::editReaderWindow()
{
    this->setDisabled(true);
    QListView *lv=ReadersMain::findChild<QListView*>("listView");
    QModelIndex index=lv->currentIndex();
    qDebug()<<index.data(Qt::DisplayRole).toString();
    QString id=index.data(Qt::DisplayRole).toString();
    for(int i=0;i<id.length();i++)
    {
        if(id[i]=='.')
        {
            id.chop(id.length()-i);
            qDebug()<<"id"<<id.toInt();
            readerWindow.setReaderId(id.toInt());
            break;
        }
    }
    readerWindow.show();
    readerWindow.exec();
    updateList();
    this->setDisabled(false);
}

void ReadersMain::deleteReader()
{
    extern databaseHandler db;
    this->setDisabled(true);

    QListView *lv=ReadersMain::findChild<QListView*>("listView");
    QModelIndex index=lv->currentIndex();
    qDebug()<<index.data(Qt::DisplayRole).toString();
    QString id=index.data(Qt::DisplayRole).toString();

    for(int i=0;i<id.length();i++)
    {
        if(id[i]=='.')
        {
            id.chop(id.length()-i);
            qDebug()<<"id"<<id.toInt();
            db.deleteReader(id.toInt());
            break;
        }
    }
    updateList();
    this->setDisabled(false);
}

void ReadersMain::enableButtons()
{
    ReadersMain::findChild<QPushButton*>("editButton")->setEnabled(true);
    ReadersMain::findChild<QPushButton*>("deleteButton")->setEnabled(true);
}
