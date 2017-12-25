#include "basicdrawpanel.h"

BasicDrawPanel::BasicDrawPanel(QWidget *parent, int board, int row, int column):
    QPushButton(parent), cross(false), click(false), board(board), row(row), column(column)
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

void BasicDrawPanel::doMove()
{
    emit playMove(board, row, column);
}
