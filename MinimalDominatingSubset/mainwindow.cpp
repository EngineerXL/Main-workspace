#include "mainwindow.h"
#include "solution.h"
#include "ui_mainwindow.h"

#include <cmath>

#define pi 3.1415926535

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMaximum(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    int k=0, n=ui->spinBox->value();
    QString qs=ui->textEdit_1->toPlainText();
    std::vector< std::vector<int> > a(n, std::vector<int>(n, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(k>=qs.size()) break;
            while(k<qs.size() and qs[k]!='0' and qs[k]!='1') k++;
            a[i][j]=(qs[k]=='1'? 1:0);
            k++;
        }
    }

    QString ans=solve(n, a);
    ui->textEdit_2->setText(ans);
}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    int n=ui->spinBox->value();
    double x0=290.0, y0=290.0, r=200.0;
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(20, 20, 560, 560);
    if(n==0) return;
    double data_x[n], data_y[n];
    painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    double step =2*pi/(double)n;
    double i=0;
    for(int j=0; j<n; j++){
        data_x[j]=x0+r*sin(i)+10;
        data_y[j]=y0+r*cos(i)+10;
        painter.drawEllipse(x0+r*sin(i), y0+r*cos(i), 20, 20);
        painter.drawText(x0+5+r*sin(i), y0+15+r*cos(i), QString::number(j+1));
        i+=step;
    }

    int k=0;
    QString qs=ui->textEdit_1->toPlainText();
    std::vector< std::vector<int> > a(n, std::vector<int>(n, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(k>=qs.size()) break;
            while(k<qs.size() and qs[k]!='0' and qs[k]!='1') k++;
            a[i][j]=(qs[k]=='1'? 1:0);
            k++;
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(a[i][j]==0) continue;
            double dy=data_y[j]-data_y[i], dx=data_x[j]-data_x[i];
            double angle=atan(dy/dx);
            if(dx>0) angle=pi+angle;
            painter.drawLine(data_x[i]-10*cos(angle), data_y[i]-10*sin(angle), data_x[j]+10*cos(angle), data_y[j]+10*sin(angle));
            if(a[j][i]==0){
                double side=14.0;
                QPointF points[3]={QPointF(data_x[j]+10*cos(angle), data_y[j]+10*sin(angle)), QPointF(data_x[j]+10*cos(angle)+side*cos(angle+pi/6), data_y[j]+10*sin(angle)+side*sin(angle+pi/6)), QPointF(data_x[j]+10*cos(angle)+side*cos(angle-pi/6), data_y[j]+10*sin(angle)+side*sin(angle-pi/6))};
                painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                painter.drawPolygon(points, 3);
            }
        }
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    repaint();
}
