#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDomNode>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

static const QString TEMP_FILE_POSTFIX = "_temp";
static const QString TEMP_PATH = "/tmp/";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnExit_clicked();
    void on_btnSave_clicked();
    void on_btnSaveAs_clicked();
    void on_btnOpen_clicked();
    void on_btnClear_clicked();
    void on_textEdit_textChanged();
    void on_cbDOM_clicked();
    void on_cbSAX_clicked();
    void on_btnUpdate_clicked();
    void autosave();

private:
    Ui::MainWindow *ui;
    QString fName;

    void saveFile();
    void setUpdateAvailability(bool);
    void traverseNode(const QDomNode &, QTreeWidgetItem &treeRootItem);
};

#endif // MAINWINDOW_H
