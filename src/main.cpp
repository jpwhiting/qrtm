#include <cstdlib>
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QStringListIterator>
#include <QWebView>

#include "rtm.h"
#include "authentication.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RTM::Authentication a("8c7873b30bec5c4f069264ddcfa7fdbf", "13316d7400dc68c8", RTM::Delete, "", &app);
    a.beginAuth();
    /*RtmAPI r("8c7873b30bec5c4f069264ddcfa7fdbf", "13316d7400dc68c8");
    //r.login("RTMinder Login");
    qDebug() << r.getToken();
    qDebug() << r.testLogin();
    QString str("\"sertac\":12");
    QStringList l = str.split(',', QString::KeepEmptyParts);
    QStringListIterator i(l);

    while(i.hasNext()){
        std::cout << i.next().toStdString() << std::endl;
    }
    */

    return app.exec();
}

