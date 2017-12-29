#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtWidgets/QGridLayout>
#include <QActionGroup>
#include "Matrix.h"
#include "basicdrawpanel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void playMove(int board, int row, int column);
    void onEasy();
    void onMedium();
    void onHard();
    void onExtreme();
    void onUnwinnable();
    void reset();
    void showInfo();

private:
    void createActions();
    void doComputerMove();
    void showNextBoard();

    typedef matrix<BasicDrawPanel*, 3, 3> DrawPanel;

    Ui::MainWindow *ui;
    QActionGroup *difficulty;
    QAction *easy;
    QAction *medium;
    QAction *hard;
    QAction *extreme;
    QAction *unwinnable;
    QVector<DrawPanel> drawPanels;
    QVector<QGridLayout*> playField;
    SuperTTT* game;
    int difficultySetting;
    bool computerFirst;
};

#endif // MAINWINDOW_H
