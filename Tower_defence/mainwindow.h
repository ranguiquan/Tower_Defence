#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QPushButton>
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
    void show_lose()
    {
        if(world.lose==1)
            QMessageBox::warning(NULL, "warning", "YOU LOSE!");
    }

protected:
    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);  
    void mouseReleaseEvent(QMouseEvent* e);

private:
    Ui::MainWindow *ui;
    QTimer* refresher;//刷新用计时器
    QTimer* addMoney;//定时加金币
    QTimer* setscene;//切换场景
    Scene world;

private slots:
    void add_money();
    void set_Scene();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
