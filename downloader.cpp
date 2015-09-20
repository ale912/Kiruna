#include "downloader.h"

Downloader::Downloader(QObject *obj):
    QObject(obj)
{
    _networkManager = new QNetworkAccessManager(this);

    connect(_networkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onFinished(QNetworkReply*)));
}

void Downloader::onFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
        emit error();
    else{
        emit done(reply->url(), reply->readAll());
    }
    reply->deleteLater();
}

void Downloader::download(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply* reply = _networkManager->get(request);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            SIGNAL(downloadProgress(qint64,qint64)));
}

