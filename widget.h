#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QStack>
#include <QDate>
#include "downloader.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void start();
    void downloadProgress(qint64 received, qint64 total);
    void error();
    void done(const QUrl&url, const QByteArray&data);

private:
    Ui::Widget *ui;

    QString LINK;
    QDate date1, date2;
    Downloader* _downloader;
    QDate& getDate(const QString &str);
};

#endif // WIDGET_H
