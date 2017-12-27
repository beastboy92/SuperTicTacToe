#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SuperTTT.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    drawPanels(10),
    playField(9),
    difficultySetting(1),
    computerFirst(false)
{
    ui->setupUi(this);
    createActions();

    game = new SuperTTT(computerFirst ? SuperTTT::HUMAN : SuperTTT::COMPUTER, difficultySetting);

    // create all the buttons
    for (int board = 1; board < 10; ++board)
    {
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column)
            {
                drawPanels[board](row, column) = new BasicDrawPanel(ui->centralWidget, board, row, column);
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
                drawPanels[i+1](row, column)->reset();
            }
        }
        ui->centralGrid->addLayout(playField[i], i/3, i%3, 1 ,1);
    }

    connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(reset()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playMove(int board, int row, int column)
{
    //qDebug() << "board: " << board << " row: " << row << " column: " << column;
    SuperTTT::Side turn;
    if(game->isUndecided())
    {
        if(game->giveLastPlayer() == SuperTTT::HUMAN)
        {
            turn = SuperTTT::COMPUTER;
        }
        else if(game->giveLastPlayer() == SuperTTT::COMPUTER)
        {
            turn = SuperTTT::HUMAN;
        }

        if(game->playMove(turn, board, row, column))
        {
            game->setLastPlayer(turn);
            game->checkWins(turn);
            drawPanels[board](row, column)->showMove(turn);
            ui->statusBar->showMessage(QString("Next board = %1").arg((column+1)+(row*3)));

            if(turn == SuperTTT::HUMAN && !ui->actionPVP->isChecked())
            {
                doComputerMove();
            }
        }
    }

    if (game->isAWin(SuperTTT::COMPUTER, 0) && !ui->actionPVP->isChecked()) {
        ui->statusBar->showMessage("Computer wins!!");
    }
    else if (game->isAWin(SuperTTT::COMPUTER, 0) && ui->actionPVP->isChecked()) {
        ui->statusBar->showMessage("Player 2 wins!!");
    }
    else if (game->isAWin(SuperTTT::HUMAN, 0)) {
        ui->statusBar->showMessage("Player wins!!");
    }
    else if (game->boardIsFull(0)) {
        ui->statusBar->showMessage("Draw!!");
    }
}

void MainWindow::onEasy()
{
    difficultySetting = 1;
    reset();
}

void MainWindow::onMedium()
{
    difficultySetting = 5;
    reset();
}

void MainWindow::onHard()
{
    difficultySetting = 9;
    reset();
}

void MainWindow::onExtreme()
{
    difficultySetting = 10;
    reset();
}

void MainWindow::onUnwinnable()
{
    difficultySetting = 12;
    reset();
}

void MainWindow::reset()
{
    delete game;
    computerFirst = !computerFirst;
    game = new SuperTTT(computerFirst ? SuperTTT::HUMAN : SuperTTT::COMPUTER, difficultySetting);

    //reset all panels
    std::for_each(drawPanels.cbegin() + 1, drawPanels.cend(), [](DrawPanel panel){
        for (auto p : panel){
            p->reset();
        }
    });

    ui->statusBar->showMessage("New Game");
    if (computerFirst && !ui->actionPVP->isChecked()){
        doComputerMove();
    }
}

void MainWindow::createActions()
{
    difficulty = new QActionGroup(ui->menuDifficulty);
    easy = new QAction("Easy", difficulty);
    easy->setCheckable(true);
    connect(easy, SIGNAL(triggered()), this, SLOT(onEasy()));

    medium = new QAction("Medium", difficulty);
    medium->setCheckable(true);
    connect(medium, SIGNAL(triggered()), this, SLOT(onMedium()));

    hard = new QAction("Hard", difficulty);
    hard->setCheckable(true);
    connect(hard, SIGNAL(triggered()), this, SLOT(onHard()));

    extreme = new QAction("Extreme", difficulty);
    extreme->setCheckable(true);
    connect(extreme, SIGNAL(triggered()), this, SLOT(onExtreme()));

    unwinnable = new QAction("Unwinnable", difficulty);
    unwinnable->setCheckable(true);
    connect(unwinnable, SIGNAL(triggered()), this, SLOT(onUnwinnable()));

    easy->setChecked(true);

    ui->menuDifficulty->addAction(easy);
    ui->menuDifficulty->addAction(medium);
    ui->menuDifficulty->addAction(hard);
    ui->menuDifficulty->addAction(extreme);
    ui->menuDifficulty->addAction(unwinnable);
}

void MainWindow::doComputerMove()
{
    if(game->isUndecided())
    {
        ui->statusBar->showMessage("Computer is deciding a move");

        int bestRow, bestColumn, bestBoard;
        game->findFirstValidMove(bestRow, bestColumn, bestBoard);
        game->chooseComputerMove(bestRow, bestColumn, bestBoard);

        playMove(bestBoard, bestRow, bestColumn);
    }
}
