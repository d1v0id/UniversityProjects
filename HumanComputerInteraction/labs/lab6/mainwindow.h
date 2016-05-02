#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QDomNode>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSignIn_clicked();
    void on_btnGetImage_clicked();
    void on_btnSearch_clicked();
    void on_update_weather();
    void on_auth_reply_finished();
    void on_go_get_it_finished();
    void on_get_weather_finished();
    void on_get_weather_image_finished();

private:
    Ui::MainWindow *ui;
    QString weatherTemperature;
    QString weatherImage;
    QString weatherType;

    void traverse_node(const QDomNode &);
};

#endif // MAINWINDOW_H
