#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include <QtGlobal>
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> xVec,yVec;
};

#endif // MAINWINDOW_H
