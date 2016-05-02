#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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
    void on_open_text_clicked();
    void on_save_text_clicked();
    void on_clear_text_clicked();
    void on_exit_text_clicked();
    void autosave();
    void expired();

private:
    Ui::MainWindow *ui;
    QString fName;
};

#endif // MAINWINDOW_H
