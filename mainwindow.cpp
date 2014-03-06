#include "mainwindow.h"
#include "ui_mainwindow.h"




using namespace std;

//Расстояние от центра окружности до точки
qreal Line_D (QPointF cPnt, QPointF pPnt)
{
    return sqrt(pow((pPnt.x() - cPnt.x()), 2) + pow((pPnt.y() - cPnt.y()), 2));
}

// Точка O0-------------------------------
QPointF O0 (QPointF cPnt, QPointF pPnt)
{
    QPointF tmpPoint(0.0, 0.0);
    tmpPoint.setX( pPnt.x() + (cPnt.x() - pPnt.x())/2 );
    tmpPoint.setY( pPnt.y() + (cPnt.y() - pPnt.y())/2 );

    return tmpPoint;
}

//Длина a--------------------------------
qreal Line_A (qreal d, qreal R)
{
    return ( ( (2 * pow(d, 2) ) - pow(R, 2) ) / (2*d) );
}

//Длина h---------------------------------
qreal Line_H (qreal d, qreal a)
{
    return sqrt( ( pow(d, 2) - pow(a, 2)));
}

//Координаты точки H
QPointF Point_H (QPointF O0, QPointF cPnt, qreal a, qreal d)
{
    QPointF tmpPoint(0.0, 0.0);
    tmpPoint.setX( O0.x() + a*(cPnt.x() - O0.x())/d );
    tmpPoint.setY( O0.y() + a*(cPnt.y() - O0.y())/d );

    return tmpPoint;
}

//------Искомые точки--------------------------------------
QPointF findPoint_P1 (QPointF PntH, QPointF cPnt, QPointF O0, qreal h, qreal d)
{
    QPointF tmpPoint(0.0, 0.0);
    tmpPoint.setX( PntH.x() + h*(cPnt.y() - O0.y())/d );
    tmpPoint.setY( PntH.y() + h*(cPnt.x() - O0.x())/d );

    return tmpPoint;
}

QPointF findPoint_P2 (QPointF Point_H, QPointF cPnt, QPointF O0, qreal h, qreal d)
{
    QPointF tmpPoint(0.0, 0.0);
    tmpPoint.setX( Point_H.x() - h*(cPnt.y() - O0.y())/d );
    tmpPoint.setY( Point_H.y() - h*(cPnt.x() - O0.x())/d );

    return tmpPoint;
}

//----------Вывод значений-----------------------------------------
int findPointsOfTangets (QPointF cPnt, qreal R, QPointF pPnt, QVector<QPointF> &vPoints)
{
    qDebug() << "Point of center circle = " << cPnt;
    qDebug() << "Radius of circle = " << R;
    qDebug() << "Point = " << pPnt;

    qreal D = Line_D(cPnt, pPnt);
    qreal d = D/2;
    qreal a = Line_A(d,R);
    qreal h = Line_H(d,a);

    QPointF Pnt_0 = O0(cPnt, pPnt);
    QPointF PntH = Point_H(Pnt_0, cPnt, a, d);

    if (D <= R)
    {
        cout << "Tangent does not exist. \n";
        return 0;
    }
    else
    {
         d = D/2;
    }

    //Искомые точки касательных
    QPointF P1 = findPoint_P1 (PntH, cPnt, Pnt_0, h, d);
    QPointF P2 = findPoint_P2 (PntH, cPnt, Pnt_0, h, d);

    //qDebug() << "Point P1" << P1;
    //qDebug() << "Point P2" << P2;

    vPoints.append( P1 );
    vPoints.append( P2 );




    return 1;
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget( ui->graphicsView );

    scene = new QGraphicsScene();
    ui->graphicsView->setScene( scene );


    double sc_value = 25.0;
    ui->graphicsView->scale(sc_value, sc_value);

    QPointF cpCircle(1.0, 1.0);
    qreal R = 2.5;
    QPointF pPoint(15.0, -10.0);
    QVector<QPointF> vPoints;


    findPointsOfTangets (cpCircle, R, pPoint, vPoints);

    scene->addEllipse(cpCircle.x() - R, cpCircle.y() - R, 2*R, 2*R);

    qreal r = 0.2;
    QPen p_line;
    p_line.setColor(Qt::blue);
    QBrush pBrush(Qt::blue);
    scene->addEllipse(pPoint.x() - r, pPoint.y() - r, 2*r, 2*r, p_line, pBrush );

    QLineF fLine(vPoints.at(0), pPoint);
    QLineF sLine(vPoints.at(1), pPoint);


    scene->addLine( fLine );
    scene->addLine( sLine );

//Продолжение прямой от точки касания
    QPointF tmpPoint = fLine.pointAt( -1 );
    QLineF tmpLine (vPoints.at(0), tmpPoint);
    QPen tmpPen(Qt::red);

    scene->addLine(tmpLine, tmpPen);




    ui->graphicsView->update();

}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}
