#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql>

class databaseHandler
{
    private:
    QSqlDatabase database;
    QString connectionName;
public:
    databaseHandler();
    ~databaseHandler();
    void createDatabase();
    QStringList getBorrowings();
    QStringList getAllBorrowings();
    QStringList getAllBooks();
    QStringList getReaders();
    QStringList getBookById(int id);
    void init(QString name);
    QStringList getReaderById(int id);
    void updateBook(int id, QString title, QString author, QString releaseDate);
    void deleteBook(int id);
    void updateReader(int id, QString title, QString author, QString gender);
    void deleteReader(int id);
    void insertBook(QString title, QString author, QString releaseDate);
    void insertReader(QString title, QString author, QString releaseDate);
    void endBorrow(int id);
    QStringList getAvailableBooks();
    void borrow(int bookId, int readerId, QString date);
    void extendBorrow(int id, QString date);
    QStringList getBorrowInfoById(int id);
};

#endif // DATABASEHANDLER_H
