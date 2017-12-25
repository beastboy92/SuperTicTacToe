#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtWidgets/QGridLayout>
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

private:
    typedef matrix<BasicDrawPanel*, 3, 3> DrawPanel;

    Ui::MainWindow *ui;
    QVector<DrawPanel> drawPanels;
    QVector<QGridLayout*> playField;

};

#endif // MAINWINDOW_H
