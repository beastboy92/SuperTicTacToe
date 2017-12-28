#include "basicdrawpanel.h"

BasicDrawPanel::BasicDrawPanel(QWidget *parent, int board, int row, int column):
    QPushButton(parent), board(board), row(row), column(column)
{
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    QFont font;
    font.setPointSize(30);
    this->setFont(font);

    connect(this, SIGNAL(clicked()), this, SLOT(doMove()));
}

void BasicDrawPanel::showMove(SuperTTT::Side s)
{
    if(s == SuperTTT::HUMAN)
    {
        this->setText("X");
        this->setStyleSheet(QStringLiteral("background-color: rgb(102, 153, 255);"
                                            "color: rgb(0, 0, 0);"));
    }
    else if(s == SuperTTT::COMPUTER)
    {
        this->setText("O");
        this->setStyleSheet(QStringLiteral("background-color: rgb(255, 77, 77);"
                                            "color: rgb(0, 0, 0);"));
    }
    this->setDisabled(true);
}

void BasicDrawPanel::disableTile()
{
    if(this->text().isEmpty())
    {
        this->setStyleSheet(QStringLiteral("background-color: rgb(128, 128, 128);"));
        this->setDisabled(true);
    }
}

void BasicDrawPanel::enableTile()
{
    if(this->text().isEmpty())
    {
        this->setStyleSheet(QStringLiteral("background-color: rgb(191, 191, 191);"));
        this->setDisabled(false);
    }
}

void BasicDrawPanel::reset()
{
    this->setText("");
    this->setDisabled(false);
    this->setStyleSheet(QStringLiteral("background-color: rgb(191, 191, 191);"
                                        "color: rgb(0, 0, 0);"));
}

void BasicDrawPanel::doMove()
{
    emit playMove(board, row, column);
}
