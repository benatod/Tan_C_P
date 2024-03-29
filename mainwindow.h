#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <math.h>


#include <QPointF>
#include <QDebug>
#include <QGraphicsScene>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
     QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
