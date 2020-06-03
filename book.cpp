#include "book.h"
#include "ui_book.h"

book::book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::book)
{
    ui->setupUi(this);

    QPushButton *confirm=book::findChild<QPushButton*>("confirmButton");
    connect(confirm,SIGNAL(released()),this,SLOT(addOrUpdate()));
}

book::~book()
{
    delete ui;
}

void book::setBookId(int id)
{
    bookId=id;
    qDebug()<<"id"<<id;
    prepare();
}

void book::prepare()
{
    QTextEdit *title=book::findChild<QTextEdit*>("titleEdit");
    QTextEdit *author=book::findChild<QTextEdit*>("authorEdit");
    QDateEdit *releaseDate=book::findChild<QDateEdit*>("dateEdit");
    QLabel *bookIdLabel=book::findChild<QLabel*>("bookIdLabel");

    extern databaseHandler db;

    if(bookId>0)
    {
       QStringList book = db.getBookById(bookId);
       title->setText(book[1]);
       author->setText(book[2]);
       qDebug()<<"bookDate"<<book[3];

       QDate date=QDate::fromString(book[3],"yyyy-MM-dd");
       qDebug()<<"QDate"<<date;
       releaseDate->setDate(date);
       bookIdLabel->setText("Numer książki: "+book[0]);
    }
    else
    {
        title->setText("");
        author->setText("");
        releaseDate->setDate(QDate::fromString("2000-02-01","yyyy-MM-dd"));
        bookIdLabel->setText("Numer książki: ");
    }
}

void book::addOrUpdate()
{
    qDebug()<<"addOrUpdate book";
    extern databaseHandler db;
    QTextEdit *title=book::findChild<QTextEdit*>("titleEdit");
    QTextEdit *author=book::findChild<QTextEdit*>("authorEdit");
    QDateEdit *releaseDate=book::findChild<QDateEdit*>("dateEdit");
    qDebug()<<bookId;
    if(bookId<1)
    {
        db.insertBook(title->toPlainText(),author->toPlainText(),releaseDate->date().toString("yyyy-MM-dd"));
    }
    else
    {
        db.updateBook(bookId,title->toPlainText(),author->toPlainText(),releaseDate->date().toString("yyyy-MM-dd"));
    }
    this->close();
}
