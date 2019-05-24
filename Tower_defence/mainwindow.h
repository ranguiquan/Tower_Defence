#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include "Scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* e);
protected:
    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);  
    void mouseReleaseEvent(QMouseEvent* e);

private:
    Ui::MainWindow *ui;
    QTimer* refresher;//刷新用计时器
    QTimer* addMoney;//定时加金币
    Scene world;
private slots:
    void add_money();

};

#endif // MAINWINDOW_H
