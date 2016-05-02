#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QWebElement>
#include <QWebFrame>
#include <QTextCodec>
#include <QDomDocument>
#include <QDomElement>
#include <QTimer>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cbServices->addItem("Duck Duck Go");
    ui->cbServices->addItem("Google");
    ui->cbServices->addItem("Яндекс");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_update_weather()));
    timer->start(10000);
    timer->start(3600000);

    on_update_weather();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSignIn_clicked()
{
    QUrl urlDoLogin("https://passport.yandex.ru/auth");
    QString userName = ui->leLogin->text(); // userlab6
    QString password = ui->lePassword->text(); // userlab6password

    QByteArray postData;
    postData.append("login=" + userName);
    postData.append("&passwd=" + password);

    QNetworkRequest request(urlDoLogin);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Host", "passport.yandex.ru");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Cache-Control", "max-age=0");

    QNetworkAccessManager *manager = ui->webView->page()->networkAccessManager();
    QNetworkReply *reply = manager->post(request, postData);
    connect(reply, SIGNAL(finished()), this, SLOT(on_auth_reply_finished()));
}

void MainWindow::on_btnGetImage_clicked()
{
    QWebElement doc = ui->webView->page()->mainFrame()->documentElement();
    QWebElement element = doc.findFirst("SPAN[class='domik-user-login']");
    ui->lbEmail->setText(element.toPlainText());

    QNetworkAccessManager *manager = ui->webView->page()->networkAccessManager();
    QUrl url("https://avatars.mds.yandex.net/get-yapic/38135/326780308-25781758/islands-retina-50?rnd=797369");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(on_go_get_it_finished()));
}

void MainWindow::on_btnSearch_clicked()
{
    QString searchQuery;
    int searchVariant = ui->cbServices->currentIndex();

    switch (searchVariant) {
    case 0:
        searchQuery = "https://duckduckgo.com/?q=";
        break;

    case 1:
        searchQuery = "https://www.google.ru/#newwindow=1&q=";
        break;

    case 2:
        searchQuery = "http://yandex.ru/search/?text=";
        break;
    }

    searchQuery += ui->leSearchField->text();

    ui->webView->load(QUrl(searchQuery));
}

void MainWindow::on_update_weather()
{
    QNetworkAccessManager *manager = ui->webView->page()->networkAccessManager();
    QUrl url("http://export.yandex.ru/weather-ng/forecasts/29634.xml");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(on_get_weather_finished()));
}

void MainWindow::on_auth_reply_finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        ui->webView->load(reply->url());
    }
    else {
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

void MainWindow::on_go_get_it_finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray jpegData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(jpegData);
        ui->lbPicture->setPixmap(pixmap);
    }
    else {
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

void MainWindow::on_get_weather_finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray weatherData = reply->readAll();
        //qDebug() << weatherData;

        QDomDocument domDoc;
        domDoc.setContent(weatherData);
        QDomElement domElement = domDoc.documentElement();
        traverse_node(domElement);

        // "http://img.yandex.net/i/wiz" + weatherImage + ".png"

        if (!weatherType.isEmpty()) {
            ui->lbWeatherType->setText("Новосибирск: " + weatherType);
        }

        if (!weatherTemperature.isEmpty()) {
            ui->lbTemperature->setText(weatherTemperature + "<sup>o</sup>C");
        }

        QNetworkAccessManager *manager = ui->webView->page()->networkAccessManager();

        if (!weatherImage.isEmpty()) {
            QUrl url("http://img.yandex.net/i/wiz" + weatherImage + ".png");
            QNetworkRequest request(url);
            QNetworkReply *reply = manager->get(request);
            connect(reply, SIGNAL(finished()), this, SLOT(on_get_weather_image_finished()));
        }

    }
    else {
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

void MainWindow::on_get_weather_image_finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray jpegData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(jpegData);
        ui->lbWeatherImage->setPixmap(pixmap);
    }
    else {
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

void MainWindow::traverse_node(const QDomNode &node)
{
    QDomNode domNode = node.firstChild();
    while (!domNode.isNull()) {
        if (domNode.isElement()) {
            QDomElement domElement = domNode.toElement();

            if (!domElement.isNull()) {
                if (domElement.tagName().compare("fact") == 0) {
                    QDomNodeList childNodes = domElement.childNodes();

                    for (int i = 0; i < childNodes.size(); i++) {
                        QDomNode child = childNodes.at(i);
                        QDomElement childElement = child.toElement();
                        if (childElement.tagName().compare("temperature") == 0) {
                            weatherTemperature = childElement.text();
                        }

                        if (childElement.tagName().compare("image") == 0) {
                            weatherImage = childElement.text();
                        }

                        if (childElement.tagName().compare("weather_type") == 0) {
                            weatherType = childElement.text();
                        }

                    }

                }
            }
        }

        traverse_node(domNode);
        domNode = domNode.nextSibling();
    }
}
