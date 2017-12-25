#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    drawPanels(10),
    playField(9)
{
    ui->setupUi(this);

    // create all the buttons
    for (int board = 1; board < 10; ++board)
    {
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column)
            {
                drawPanels[board](row, column) = new BasicDrawPanel(ui->centralWidget, board, row, column);
                //TODO: connect push signal with play move slot
                connect(drawPanels[board](row, column), SIGNAL(playMove(int,int,int)), this, SLOT(playMove(int,int,int)));
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        playField[i] = new QGridLayout();
        playField[i]->setSpacing(2);
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column)
            {
                playField[i]->addWidget(drawPanels[i+1](row, column), row, column);
                drawPanels[i+1](row, column)->setStyleSheet(QStringLiteral("background-color: rgb(191, 191, 191);"));
            }
        }
        ui->centralGrid->addLayout(playField[i], i/3, i%3, 1 ,1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playMove(int board, int row, int column)
{
    qDebug() << "board: " << board << " row: " << row << " column: " << column;
}
