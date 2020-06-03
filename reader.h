#ifndef READER_H
#define READER_H

#include <QDialog>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QRadioButton>
#include "databasehandler.h"

namespace Ui {
class reader;
}

class reader : public QDialog
{
    Q_OBJECT

public:
    explicit reader(QWidget *parent = nullptr);
    ~reader();
public slots:
    void setReaderId(int i);
private slots:
    void addOrUpdate();
private:
    Ui::reader *ui;
    int readerId;
    void prepare();
};

#endif // READER_H
