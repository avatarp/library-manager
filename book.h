#ifndef BOOK_H
#define BOOK_H

#include <QDialog>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QDate>
#include "databasehandler.h"


namespace Ui {
class book;
}

class book : public QDialog
{
    Q_OBJECT

public:
    explicit book(QWidget *parent = nullptr);
    ~book();
public slots:
    void setBookId(int id);
private slots:
    void addOrUpdate();
private:
    Ui::book *ui;
    int bookId;
    void prepare();
};

#endif // BOOK_H
