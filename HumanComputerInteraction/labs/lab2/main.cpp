#include <mydialog.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDialog dg;
    dg.show();

    return a.exec();
}
