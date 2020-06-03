#include "borrowingwindow.h"
#include "ui_borrowingwindow.h"

borrowingWindow::borrowingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrowingWindow)
{
    ui->setupUi(this);

    QPushButton *addBook=borrowingWindow::findChild<QPushButton*>("confirmButton");
    connect(addBook, SIGNAL(released()),this,SLOT(borrowOrExtend()));

    QPushButton *closeButton=borrowingWindow::findChild<QPushButton*>("cancelButton");
    connect(closeButton, SIGNAL(released()),this,SLOT(close()));
}

borrowingWindow::~borrowingWindow()
{
    delete ui;
}

void borrowingWindow::setId(int id)
{
    borrowId=id;
    prepare();
}

void borrowingWindow::prepare()
{
    QListView *booksList=borrowingWindow::findChild<QListView*>("booksList");
    QListView *readersList=borrowingWindow::findChild<QListView*>("readersList");
    QDateEdit *date=borrowingWindow::findChild<QDateEdit*>("dateEdit");

    QLabel *readerLabel=borrowingWindow::findChild<QLabel*>("readersLabel");
    QLabel *booksLabel=borrowingWindow::findChild<QLabel*>("booksLabel");

    date->setDate(QDate::currentDate().addDays(1));
    date->setMinimumDate(QDate::currentDate().addDays(1));

    isReaderSelected=false;
    isBookSelected=false;

    extern databaseHandler db;

    if(borrowId<1)
    {

        booksList->setEnabled(true);
        readersList->setEnabled(true);

        readerLabel->setText("Czytelnicy:");
        booksLabel->setText("Dostępne książki:");

        extern databaseHandler db;
        QStringListModel *bookModel;
        bookModel = new QStringListModel(this);

        bookModel->setStringList(db.getAvailableBooks());
        booksList->setModel(bookModel);
        connect(booksList->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this,SLOT(bookSelected()));

        QStringListModel *readerModel;
        readerModel = new QStringListModel(this);
        readerModel->setStringList(db.getReaders());
        readersList->setModel(readerModel);
        connect(readersList->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this,SLOT(readerSelected()));
    }
    else
    {
        booksList->setEnabled(false);
        readersList->setEnabled(false);

        QStringList borrow=db.getBorrowInfoById(borrowId);

        readerLabel->setText(borrow[0]+" "+borrow[1]);
        booksLabel->setText(borrow[2]);
        date->setDate(QDate::fromString(borrow[3],"yyyy-MM-dd"));
        date->setMinimumDate(QDate::currentDate());

        borrowingWindow::findChild<QPushButton*>("confirmButton")->setEnabled(true);
    }

}

void borrowingWindow::bookSelected()
{
    isBookSelected=true;
    if(isReaderSelected)
    {
        borrowingWindow::findChild<QPushButton*>("confirmButton")->setEnabled(true);
    }
}

void borrowingWindow::readerSelected()
{
    isReaderSelected=true;
    if(isBookSelected)
    {
        borrowingWindow::findChild<QPushButton*>("confirmButton")->setEnabled(true);
    }
}

void borrowingWindow::borrowOrExtend()
{
    QListView *booksList=borrowingWindow::findChild<QListView*>("booksList");
    QListView *readersList=borrowingWindow::findChild<QListView*>("readersList");
    QDateEdit *date=borrowingWindow::findChild<QDateEdit*>("dateEdit");

    extern databaseHandler db;

    if(borrowId==0)
    {
        QModelIndex bookIndex=booksList->currentIndex();
        qDebug()<<bookIndex.data(Qt::DisplayRole).toString();
        QString bookId=bookIndex.data(Qt::DisplayRole).toString();
        QModelIndex readerIndex=readersList->currentIndex();
        qDebug()<<readerIndex.data(Qt::DisplayRole).toString();
        QString readerId=readerIndex.data(Qt::DisplayRole).toString();

        for(int i=0;i<bookId.length();i++)
        {
            if(bookId[i]=='.')
            {
                bookId.chop(bookId.length()-i);
                qDebug()<<"book id"<<bookId.toInt();
                break;
            }
        }

        for(int i=0;i<readerId.length();i++)
        {
            if(readerId[i]=='.')
            {
                readerId.chop(readerId.length()-i);
                qDebug()<<"reader id"<<readerId.toInt();
                break;
            }
        }

        db.borrow(bookId.toInt(),readerId.toInt(),date->date().toString("yyyy-MM-dd"));

    }
    else
    {
        db.extendBorrow(borrowId,date->date().toString("yyyy-MM-dd"));
    }


    this->close();
}
