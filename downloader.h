#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class Downloader: public QObject
{
    Q_OBJECT
public:
    Downloader(QObject* obj = 0);

    void download(const QUrl&url);

private slots:
    void onFinished(QNetworkReply*reply);
signals:
    void downloadProgress(qint64, qint64);
    void error();
    void done(const QUrl&, const QByteArray&);

private:
    QNetworkAccessManager* _networkManager;
};

#endif // DOWNLOADER_H
