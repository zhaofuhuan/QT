#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include <QtGlobal>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
        ui->customPlot->clearGraphs();//清除图像，函数接受一个int类型的返回值，返回删除的graphs数。
        ui->customPlot->legend->setVisible(false);//设置图例为不可见
        ui->customPlot->replot();//重新绘制

        QCPAxis *xAxis = ui->customPlot->xAxis;//x轴
        QCPAxis *yAxis = ui->customPlot->yAxis;//y轴
        // 为坐标轴添加标签
        xAxis->setLabel("X横轴");
        yAxis->setLabel("Y纵轴");
        ui->customPlot->addGraph(xAxis,yAxis);//设置图像坐标轴
        this->xVec.clear();
        this->yVec.clear();
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                //this->xVec = {119,116.5,114,111.5,109,106.5,104,101.5,99,96.5,94,91.5,89,86.5,84,81.5};/*this->xVec.append(qrand()%20);
                this->xVec.append(qrand()%20);
                this->xVec.append(qrand()%20);
                this->xVec.append(qrand()%20);
                //this->yVec = {9.8,9.2,8.8,8.7,8.9,8.4,8.8,9.1,9.5,10,9.8,10.5,10.4,9.3,8.4,7.3};
                this->yVec.append(qrand()%20);
                this->yVec.append(qrand()%20);
                this->yVec.append(qrand()%20);
         //this->yVec.append(qrand()%20);
        ui->customPlot->graph(0)->setData(this->xVec, this->yVec);
        ui->textEdit->append("随机坐标点为:");
        QString str = QString("(%1,%2),(%3,%4),(%5,%6)")
                .arg(this->xVec[0]).arg(this->yVec[0]).arg(this->xVec[1]).arg(this->yVec[1])
                .arg(this->xVec[2]).arg(this->yVec[2]);
        ui->textEdit->append(str);
        //ui->customPlot->graph(0)->setName("散点图片");// 设置图例名称
        //ui->customPlot->legend->setBrush(QColor(255,255,255,0));//设置图例背景
        // 设置坐标轴的范围，以看到所有数据
        ui->customPlot->graph(0)->rescaleAxes();//need
        //ui->customPlot->legend->setVisible(true); // 显示图例
        ui->customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)0);  // 线段风格(QCPGraph::LineStyle)i
        ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,QColor(qBlue(200)),5));//设置散点形状

        // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
        ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

        // 重画图像
        ui->customPlot->replot();

}


void MainWindow::on_pushButton_2_clicked()
{
            const int N = 2;
            //参考C++最小二乘拟合 (高阶最小二乘拟合)（附C++代码）作者：koko_TT
            //QVector<double> x(16), y(16); //初始化向量x和y
            //this->xVec = {119,116.5,114,111.5,109,106.5,104,101.5,99,96.5,94,91.5,89,86.5,84,81.5};//x，y的值可以随意更改，改为用户需要得到
            //this->yVec = {9.8,9.2,8.8,8.7,8.9,8.4,8.8,9.1,9.5,10,9.8,10.5,10.4,9.3,8.4,7.3};
            Eigen::MatrixXd A(this->xVec.size(), N + 1);

            for(int i=0; i<this->xVec.size(); ++i)
            {

                for(int n = 0; n<=N; n++)
                {
                    A(i,n) = pow(xVec[i], N-n);
                }
            }

            /*for (unsigned int i = 0; i < x.size(); ++i) {  // 遍历所有点

                for (int n = N, dex = 0; n >= 1; --n, ++dex) {  // 遍历N到1阶
                    A(i, dex) = pow(x[i], n);
                }

                A(i, N) = 1;  //
            }*/

            // 创建B矩阵
            Eigen::MatrixXd B(this->yVec.size(),1);
            for(int i = 0;i<yVec.size();i++)
            {
                B(i,0) = yVec[i];
            }
            /*Eigen::MatrixXd B(y.size(), 1);

            for (unsigned int i = 0; i < y.size(); ++i) {
                B(i, 0) = y[i];
            }*/
            Eigen::MatrixXd W;
            W = (A.transpose() * A).inverse() * A.transpose() * B;
            /*Eigen::MatrixXd W;
            W = (A.transpose() * A).inverse() * A.transpose() * B;*/
            /*double w[N+1];
            for(int i = 0;i <= 6;i++)
            {
                w[i] = W(i,0);
            }*/


            /*for (int i=0; i<16; ++i)
            {
                x_fit[i] = x[i];
                for (int n = N; n >= 1; --n) // 遍历N到1阶
                {
                    y_fit[i] = y_fit[i] + w[6-n]*pow(x[i], n);
                }
                y_fit[i] = y_fit[i]+w[6];
            }*/

            //绘图前先清除
            ui->customPlot->clearGraphs();//清除图像，函数接受一个int类型的返回值，返回删除的graphs数。
            ui->customPlot->legend->setVisible(false);//设置图例为不可见
            ui->customPlot->replot();//重新绘制

            QCPAxis *xAxis = ui->customPlot->xAxis;//x轴
            QCPAxis *yAxis = ui->customPlot->yAxis;//y轴

            // 为坐标轴添加标签
            xAxis->setLabel("X横轴");
            yAxis->setLabel("Y纵轴");
            ui->customPlot->addGraph(xAxis,yAxis);//设置图像坐标轴
            ui->customPlot->graph(0)->setData(this->xVec, this->yVec);
            ui->customPlot->graph(0)->setName("散点图片");// 设置图例名称
            ui->customPlot->legend->setBrush(QColor(255,255,255,0));//设置图例背景

            // 设置坐标轴的范围，以看到所有数据
            ui->customPlot->graph(0)->rescaleAxes();
            ui->customPlot->legend->setVisible(true); // 显示图例
            ui->customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)0);  // 线段风格(QCPGraph::LineStyle)i
            ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,QColor(qBlue(200)),5));//设置散点形状

            ui->customPlot->addGraph(xAxis,yAxis);
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            this->xVec.append(qrand()%20);
            QVector<double>  y(this->xVec.size()); //初始化向量x_fit和y_fit
            for(int i=0; i < this->xVec.size(); i++)
            {
                for(int n = 0; n<=N; n++)
                {
                    y[i] = y[i] + W(N-n,0)*pow(this->xVec[i],n);
                }
            }
            ui->customPlot->graph(1)->setData(this->xVec, y);
            ui->customPlot->graph(1)->setName("2阶最小二乘法拟合");// 设置图例名称
            ui->customPlot->legend->setVisible(true); // 显示图例
            // 设置坐标轴的范围，以看到所有数据
            ui->customPlot->graph(1)->rescaleAxes(true);
            ui->customPlot->graph(1)->setPen(QPen(QColor(255, 0, 0)));       // 设置画笔
            ui->customPlot->graph(1)->setLineStyle((QCPGraph::LineStyle)1);  // 线段风格(QCPGraph::LineStyle)i
            // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
            ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
            // 重画图像
            QString str2 = QString("f(x)=(%1)*x^2+(%2)*x+(%3)").arg(W(0,0)).arg(W(1,0)).arg(W(2,0));
            ui->textEdit->append(str2);
            ui->customPlot->replot();
}
