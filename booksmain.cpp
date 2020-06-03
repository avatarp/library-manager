#include "booksmain.h"
#include "booksmain.h"
#include "ui_booksmain.h"

BooksMain::BooksMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BooksMain)
{
    ui->setupUi(this);

    QPushButton *addBook=BooksMain::findChild<QPushButton*>("addButton");
    connect(addBook, SIGNAL(released()),this,SLOT(addBookWindow()));

    QPushButton *editBook=BooksMain::findChild<QPushButton*>("editButton");
    connect(editBook, SIGNAL(released()),this,SLOT(editBookWindow()));

    QPushButton *closeButton=BooksMain::findChild<QPushButton*>("closeButton");
    connect(closeButton, SIGNAL(released()),this,SLOT(close()));

    QPushButton *deleteButton=BooksMain::findChild<QPushButton*>("deleteButton");
    connect(deleteButton,SIGNAL(released()),this,SLOT(deleteBook()));

    updateList();
}

BooksMain::~BooksMain()
{
    delete ui;
}

void BooksMain::addBookWindow()
{
    this->setDisabled(true);
    bookWindow.setBookId(0);
    bookWindow.show();
    bookWindow.exec();
    updateList();
    this->setDisabled(false);
}


void BooksMain::editBookWindow()
{
    this->setDisabled(true);
    QListView *lv=BooksMain::findChild<QListView*>("listView");
    QModelIndex index=lv->currentIndex();
    qDebug()<<index.data(Qt::DisplayRole).toString();
    QString id=index.data(Qt::DisplayRole).toString();
    for(int i=0;i<id.length();i++)
    {
        if(id[i]=='.')
        {
            id.chop(id.length()-i);
            qDebug()<<"id"<<id.toInt();
            bookWindow.setBookId(id.toInt());
            break;
        }
    }
    bookWindow.show();
    bookWindow.exec();
    updateList();
    this->setDisabled(false);
}

void BooksMain::enableButtons()
{
    BooksMain::findChild<QPushButton*>("editButton")->setEnabled(true);
    BooksMain::findChild<QPushButton*>("deleteButton")->setEnabled(true);
}

void BooksMain::deleteBook()
{
   extern databaseHandler db;
   this->setDisabled(true);

   QListView *lv=BooksMain::findChild<QListView*>("listView");
   QModelIndex index=lv->currentIndex();
   qDebug()<<index.data(Qt::DisplayRole).toString();
   QString id=index.data(Qt::DisplayRole).toString();

   for(int i=0;i<id.length();i++)
   {
       if(id[i]=='.')
       {
           id.chop(id.length()-i);
           qDebug()<<"id"<<id.toInt();
           db.deleteBook(id.toInt());
           break;
       }
   }
   updateList();
   this->setDisabled(false);
}

void BooksMain::updateList()
{
    extern databaseHandler db;
    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList list;
    list<< "A"<<"B"<<"C"<<"D";
    model->setStringList(db.getAllBooks());
    QListView *lv=BooksMain::findChild<QListView*>("listView");
    lv->setModel(model);
    connect(lv->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(enableButtons()));
}
