#ifndef BORROWINGWINDOW_H
#define BORROWINGWINDOW_H

#include <QDialog>
#include "databasehandler.h"

namespace Ui {
class borrowingWindow;
}

class borrowingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit borrowingWindow(QWidget *parent = nullptr);
    ~borrowingWindow();

    void setId(int id);
private slots:
    void bookSelected();
    void readerSelected();
    void borrowOrExtend();
private:
    Ui::borrowingWindow *ui;
    int borrowId;
    bool isBookSelected=false;
    bool isReaderSelected=false;
    void prepare();
};

#endif // BORROWINGWINDOW_H
