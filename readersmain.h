#ifndef READERSMAIN_H
#define READERSMAIN_H

#include <QDialog>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include "databasehandler.h"
#include "reader.h"


namespace Ui {
class ReadersMain;
}

class ReadersMain : public QDialog
{
    Q_OBJECT

public:
    explicit ReadersMain(QWidget *parent = nullptr);
    ~ReadersMain();
private slots:
    void addReaderWindow();
    void editReaderWindow();
    void enableButtons();
    void deleteReader();
private:
    Ui::ReadersMain *ui;
    reader readerWindow;

    void updateList();
};

#endif // READERSMAIN_H
