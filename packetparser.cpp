#include "packetparser.h"
#include "./ui_packetparser.h"

PacketParser::PacketParser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PacketParser)
{
    ui->setupUi(this);
}

PacketParser::~PacketParser()
{
    delete ui;
}

void PacketParser::on_butt_pressed()
{
    QString qInput = ui->input->toPlainText();
    std::string input = qInput.toStdString();
    std::string output = packetParserService.parsePacket(input);
    QString qOutput = QString::fromStdString(output);
    ui->textBrowser->setText(qOutput);
}

