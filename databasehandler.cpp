#include "databasehandler.h"
#include "databasehandler.h"

databaseHandler::databaseHandler()
{
    qDebug()<<"Launched constructor";
    connectionName="MainWindow";

    database = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    database.setDatabaseName("library.sqlite");
    if (!database.open())
    {
        qDebug()<<"cannot open database C-tor";
        return;
    }
    QSqlQuery readers;
    QStringList list=database.tables( QSql::Tables);
    bool readersT=false, booksT=false, borrowingT=false;
    for(int i=0;i<list.length();i++)
    {
        if(list[i]=="readers")
        {
            readersT=true;
        }
        if(list[i]=="books")
        {
            booksT=true;
        }
        if(list[i]=="borrowing")
        {
            borrowingT=true;
        }
    }
    if(!(readersT && booksT && borrowingT))
    {
        qDebug()<<"invalid database";
        qDebug()<<"Rebuilding...";
        createDatabase();
    }

}

databaseHandler::~databaseHandler()
{
    qDebug()<<"Launched destructor";
    if(database.isOpen())
    {database.close();}
    database.removeDatabase(connectionName);
}
void databaseHandler::createDatabase()
{

    QSqlQuery query(database);
    query.exec("drop table if exists readers");
    query.exec("drop table if exists books");
    query.exec("drop table if exists borrowing");

    query.exec("CREATE TABLE readers (id INTEGER primary key AUTOINCREMENT, "
               "name varchar(20), surname varchar(30), gender varchar(1))");

    query.exec("CREATE TABLE books (id INTEGER primary key AUTOINCREMENT, "
               "name varchar(100), author varchar(100), release_date TEXT)");

    query.exec("CREATE TABLE borrowing (id INTEGER primary key AUTOINCREMENT, "
               "book_id INTEGER, reader_id INTEGER, return_date TEXT, returned INTEGER)");

    query.exec("insert into readers values(NULL, 'Jan', 'Kowalski', 'm')");
    query.exec("insert into readers values(NULL, 'Mariusz', 'Nowak', 'm')");
    query.exec("insert into readers values(NULL, 'Krzysztof', 'Nowak', 'm')");
    query.exec("insert into readers values(NULL, 'Helena', 'Malinowska', 'f')");
    query.exec("insert into readers values(NULL, 'Karolina', 'Kowalska', 'f')");

    query.exec("insert into books values(NULL, 'Kubuś Puchatek', 'Alan A. Milne', '1926-10-14')");
    query.exec("insert into books values(NULL, 'Harry Potter i Kamień Filozoficzny', 'J.K. Rowling', '1997-06-26')");
    query.exec("insert into books values(NULL, 'Drużyna Pierścienia', 'John Ronald Reuel Tolkien', '1954-07-29')");
    query.exec("insert into books values(NULL, 'Gra o tron', 'George R.R. Martin', '1996-08-01')");
    query.exec("insert into books values(NULL, 'FUTU.RE', 'Dmitrij Głuchowski', '2013-09-01')");

    query.exec("insert into borrowing values(NULL, '1', '2','2020-07-01','0')");

    QSqlQuery select(database);
    select.exec("select * from readers");
    qDebug() << query.lastError();


    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
    }

    select.exec("select * from books");
    qDebug() << query.lastError();

    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
    }

    select.exec("select * from borrowing");
    qDebug() << query.lastError();

    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        qDebug()<<select.value(4).toString();
    }

}

QStringList databaseHandler::getBorrowings()
{
    QSqlQuery select(database);
    qDebug()<<QSqlDatabase::drivers();
    select.exec("select borrowing.id, books.name,readers.name,readers.surname, return_date"
                " from borrowing join readers join books"
                " where book_id=books.id and reader_id=readers.id AND not returned=1");
    qDebug() <<"getBorrowings: "<< select.lastError();

    QStringList list;
    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        qDebug()<<select.value(4).toString();
        QString temp;
        temp+=select.value(0).toString()+". ";
        temp+=select.value(1).toString();
        temp+=" - ";
        temp+=select.value(2).toString();
        temp+=" ";
        temp+=select.value(3).toString();
        temp+=" do "+select.value(4).toString();
        list.append(temp);
    }
    return list;
}

QStringList databaseHandler::getAllBorrowings()
{
    QSqlQuery select(database);
    select.exec("select borrowing.id, books.name,readers.name,readers.surname, return_date"
                " from borrowing join readers join books"
                " where book_id=books.id and reader_id=readers.id");
    qDebug() <<"getAllBorrowings: "<< select.lastError();

    QStringList list;
    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        qDebug()<<select.value(4).toString();
        QString temp;
        temp+=select.value(0).toString()+". ";
        temp+=select.value(1).toString();
        temp+=" - ";
        temp+=select.value(2).toString();
        temp+=" ";
        temp+=select.value(3).toString();
        temp+=" do "+select.value(4).toString();
        list.append(temp);
    }
    return list;
}

QStringList databaseHandler::getAllBooks()
{
    QSqlQuery select(database);
    select.exec("select * from books");
    qDebug() <<"getBooks: "<< select.lastError();

    QStringList list;
    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        QString temp;
        temp=select.value(0).toString();
        temp+=".  ";
        temp+=select.value(1).toString();
        temp+=" - ";
        temp+=select.value(2).toString();
        temp+=" - "+select.value(3).toString();
        list.append(temp);
    }
    return list;
}

QStringList databaseHandler::getAvailableBooks()
{
    QSqlQuery select(database);
    select.exec("select books.id,books.name,books.author,books.release_date from books join borrowing where (NOT books.id=borrowing.book_id AND borrowing.returned=0)");
    qDebug() <<"getAvailableBooks: "<< select.lastError();

    QStringList list;
    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        QString temp;
        temp=select.value(0).toString();
        temp+=".  ";
        temp+=select.value(1).toString();
        temp+=" - ";
        temp+=select.value(2).toString();
        temp+=" - "+select.value(3).toString();
        list.append(temp);
    }
    return list;
}



QStringList databaseHandler::getReaders()
{
    QSqlQuery select(database);
    select.exec("select * from readers");
    qDebug()<<"getReaders: " << select.lastError();

    QStringList list;
    while(select.next())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        QString temp;
        temp=select.value(0).toString();
        temp+=".  ";
        temp+=select.value(1).toString();
        temp+=" ";
        temp+=select.value(2).toString();
        temp+=" - "+select.value(3).toString();
        list.append(temp);
    }
    return list;
}

QStringList databaseHandler::getBookById(int id)
{
    QStringList list;
    if(id<0)
    {
        return list;
    }
    QSqlQuery select(database);
    qDebug()<<"getBook id:"<<id;
    select.prepare("select * from books where id=?");
    select.bindValue(0,id);
    select.exec();

    if(select.first())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        list.append(select.value(0).toString());
        list.append(select.value(1).toString());
        list.append(select.value(2).toString());
        list.append(select.value(3).toString());
    }
    return list;

}



QStringList databaseHandler::getReaderById(int id)
{
    QStringList list;
    if(id<0)
    {
        return list;
    }
    QSqlQuery select(database);
    qDebug()<<"getBook id:"<<id;
    select.prepare("select * from readers where id=?");
    select.bindValue(0,id);
    select.exec();

    if(select.first())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        list.append(select.value(0).toString());
        list.append(select.value(1).toString());
        list.append(select.value(2).toString());
        list.append(select.value(3).toString());
    }
    return list;

}


void databaseHandler::updateBook(int id, QString title, QString author, QString releaseDate)
{
    QSqlQuery update(database);
    update.prepare("update books set name=? ,author=? , release_date=? where id=?");
    update.bindValue(0,title);
    update.bindValue(1,author);
    update.bindValue(2,releaseDate);
    update.bindValue(3,id);
    update.exec();
    qDebug()<<update.lastError();
}

void databaseHandler::deleteBook(int id)
{
    QSqlQuery remove(database);
    remove.prepare("delete from books where id=?");
    remove.bindValue(0,id);
    remove.exec();
}

void databaseHandler::insertBook(QString title, QString author, QString releaseDate)
{
    QSqlQuery insert(database);
    insert.prepare("insert into books (id , name , author, release_date) values (NULL, :title ,:author , :date )");
    insert.bindValue(0,title);
    insert.bindValue(1,author);
    insert.bindValue(2,releaseDate);
    insert.exec();
    qDebug()<<insert.lastError();
}

void databaseHandler::updateReader(int id, QString name, QString surname, QString gender)
{
    QSqlQuery update(database);
    update.prepare("update readers set name=? ,surname=? , gender=? where id=?");
    update.bindValue(0,name);
    update.bindValue(1,surname);
    update.bindValue(2,gender);
    update.bindValue(3,id);
    update.exec();
}

void databaseHandler::deleteReader(int id)
{
    QSqlQuery remove(database);
    remove.prepare("delete from readers where id=?");
    remove.bindValue(0,id);
    remove.exec();
}


void databaseHandler::insertReader(QString name, QString surname, QString gender)
{
    QSqlQuery insert(database);
    insert.prepare("insert into readers (name, surname, gender) values (? , ? , ? )");
    insert.bindValue(0,name);
    insert.bindValue(1,surname);
    insert.bindValue(2,gender);
    insert.exec();
}

void databaseHandler::endBorrow(int id)
{
    QSqlQuery update(database);
    update.prepare("update borrowing set returned=? where id=?");
    update.bindValue(0,"1");
    update.bindValue(1,id);
    update.exec();
    qDebug()<<"end borrow"<<update.lastError();
}

void databaseHandler::extendBorrow(int id,QString date)
{
    QSqlQuery update(database);
    update.prepare("update borrowing set return_date=? where id=?");
    update.bindValue(0,date);
    update.bindValue(1,id);
    update.exec();
    qDebug()<<"extend borrow"<<update.lastError();
}

void databaseHandler::borrow(int bookId,int readerId, QString date)
{
    QSqlQuery insert(database);
    insert.prepare("insert into borrowing (book_id, reader_id, return_date, returned) values (?,?,?,?)");
    insert.bindValue(0,bookId);
    insert.bindValue(1,readerId);
    insert.bindValue(2,date);
    insert.bindValue(3,0);
    insert.exec();
    qDebug()<<"End borrow"<<insert.lastError();
}

QStringList databaseHandler::getBorrowInfoById(int id)
{
    QStringList list;
    if(id<0)
    {
        return list;
    }
    QSqlQuery select(database);
    qDebug()<<"getBook id:"<<id;
    select.prepare("select readers.name, readers.surname, books.name, borrowing.return_date from borrowing join readers join books where borrowing.id=?");
    select.bindValue(0,id);
    select.exec();

    if(select.first())
    {
        qDebug()<<select.value(0).toString();
        qDebug()<<select.value(1).toString();
        qDebug()<<select.value(2).toString();
        qDebug()<<select.value(3).toString();
        list.append(select.value(0).toString());
        list.append(select.value(1).toString());
        list.append(select.value(2).toString());
        list.append(select.value(3).toString());
    }
    return list;
}

