#include "packetparser.h"

#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PacketParser w;

    w.show();
    return a.exec();
}
