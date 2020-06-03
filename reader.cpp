#include "reader.h"
#include "ui_reader.h"

reader::reader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reader)
{
    ui->setupUi(this);

    QPushButton *confirm=reader::findChild<QPushButton*>("confirmButton");
    connect(confirm,SIGNAL(released()),this,SLOT(addOrUpdate()));

    QPushButton *cancel=reader::findChild<QPushButton*>("cancelButton");
    connect(cancel,SIGNAL(released()),this,SLOT(close()));
}

reader::~reader()
{
    delete ui;
}

void reader::setReaderId(int i)
{
    readerId=i;
    qDebug()<<"id"<<readerId;
    prepare();
}

void reader::prepare()
{
    QTextEdit *name=reader::findChild<QTextEdit*>("nameEdit");
    QTextEdit *surname=reader::findChild<QTextEdit*>("surnameEdit");
    QRadioButton *maleRadio=reader::findChild<QRadioButton*>("maleRadio");
    QRadioButton *femaleRadio=reader::findChild<QRadioButton*>("femaleRadio");
    QLabel *readerIdLabel=reader::findChild<QLabel*>("readerIdLabel");

    extern databaseHandler db;

    if(readerId!=0)
    {
       QStringList reader = db.getReaderById(readerId);
       name->setText(reader[1]);
       surname->setText(reader[2]);
       maleRadio->setChecked(false);
       femaleRadio->setChecked(false);
       if(reader[3]=='f')
       {
           femaleRadio->setChecked(true);
       }
       else if(reader[3]=='m')
       {
           maleRadio->setChecked(true);
       }
       readerIdLabel->setText("Numer czytelnika: "+reader[0]);
    }
    else
    {
        name->setText("");
        surname->setText("");
        maleRadio->setChecked(false);
        femaleRadio->setChecked(false);
        readerIdLabel->setText("Numer czytelnika: ");
    }

}

void reader::addOrUpdate()
{
    qDebug()<<"addOrUpdate reader";
    extern databaseHandler db;
    QTextEdit *name=reader::findChild<QTextEdit*>("nameEdit");
    QTextEdit *surname=reader::findChild<QTextEdit*>("surnameEdit");
    QRadioButton *maleRadio=reader::findChild<QRadioButton*>("maleRadio");
    QRadioButton *femaleRadio=reader::findChild<QRadioButton*>("femaleRadio");
    qDebug()<<readerId;
    if(readerId<1)
    {
        if(maleRadio->isChecked())
        {   db.insertReader(name->toPlainText(),surname->toPlainText(),"m");}
        else if(femaleRadio->isChecked())
        {   db.insertReader(name->toPlainText(),surname->toPlainText(),"f");}
        else
        {   db.insertReader(name->toPlainText(),surname->toPlainText(),"");}
    }
    else
    {
        if(maleRadio->isChecked())
        {   db.updateReader(readerId,name->toPlainText(),surname->toPlainText(),"m");}
        else if(femaleRadio->isChecked())
        {   db.updateReader(readerId,name->toPlainText(),surname->toPlainText(),"f");}
        else
        {   db.updateReader(readerId,name->toPlainText(),surname->toPlainText(),"");}
    }
    this->close();
}
