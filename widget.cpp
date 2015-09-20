#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    LINK = "http://www.irf.se/rio-bin/digital-www-kir-volt?";
    _downloader = new Downloader(this);
    connect(ui->pushButtonStart, SIGNAL(clicked(bool)), SLOT(start()));
    connect(_downloader, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(_downloader, SIGNAL(done(QUrl,QByteArray)), SLOT(done(QUrl,QByteArray)));
}

Widget::~Widget()
{
    delete ui;
}

QDate& Widget::getDate(const QString& str)
{
    QStringList begin = str.split('.');
    QDate date(begin[0].toInt(), begin[1].toInt(), begin[2].toInt());
    return date;
}

void Widget::start()
{
    date1 = getDate(ui->lineEditOt->text());
    date2 = getDate(ui->lineEditDo->text());

    QString link = LINK.append(date1.toString('yyyy/MM/dd'));
    _downloader->download(QUrl(link));
}

void Widget::downloadProgress(qint64 received, qint64 total)
{
    if (total <= 0) {
        error();
        return;
    }
    ui->progressBar->setValue(100 * received / total);
}

void Widget::error()
{

}

void Widget::done(const QUrl &url, const QByteArray &data)
{
    QFile file(date1.toString('yyyyMMdd.kir'));
    if(file.open(QIODevice::WriteOnly)){
        file.write(data);
        file.close();
    }

    if(date1 < date2){
        date1 = date1.addDays(1);
        QString link = LINK.append(date1.toString('yyyy/MM/dd'));
        _downloader->download(QUrl(link));
    }
}

