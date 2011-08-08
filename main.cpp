#include <QtCore/QCoreApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int i =1;
    i=i++ + ++i;
    qDebug()<<i;

    return a.exec();
}
