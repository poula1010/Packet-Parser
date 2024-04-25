#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include <QMainWindow>
#include "PacketParserService.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PacketParser;
}
QT_END_NAMESPACE

class PacketParser : public QMainWindow
{
    Q_OBJECT

public:
    PacketParser(QWidget *parent = nullptr);
    ~PacketParser();

private slots:
    void on_butt_pressed();

private:
    Ui::PacketParser *ui;
    PacketParserService packetParserService;

};
#endif // PACKETPARSER_H
