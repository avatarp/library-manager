#ifndef BOOKSMAIN_H
#define BOOKSMAIN_H

#include <QDialog>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include "databasehandler.h"
#include "book.h"

namespace Ui {
class BooksMain;
}

class BooksMain : public QDialog
{
    Q_OBJECT

public:
    explicit BooksMain(QWidget *parent = nullptr);
    ~BooksMain();
private slots:
        void addBookWindow();
        void editBookWindow();
        void enableButtons();
        void deleteBook();
private:
    book bookWindow;
    Ui::BooksMain *ui;
    void updateList();
};

#endif // BOOKSMAIN_H
