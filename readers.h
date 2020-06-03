#ifndef READERS_H
#define READERS_H

#include <QDialog>

namespace Ui {
class Readers;
}

class Readers : public QDialog
{
    Q_OBJECT

public:
    explicit Readers(QWidget *parent = nullptr);
    ~Readers();

private:
    Ui::Readers *ui;
};

#endif // READERS_H
