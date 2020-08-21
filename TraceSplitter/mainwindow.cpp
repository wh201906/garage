﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    data_x = new QVector<double> ();
    data_y = new QVector<double> ();
    cursor_l = new QCPItemStraightLine(ui->plotWidget);
    cursor_r = new QCPItemStraightLine(ui->plotWidget);
    cursor_l->setVisible(false);
    cursor_r->setVisible(false);
    cursor_l->point1->setType(QCPItemPosition::ptPlotCoords);
    cursor_l->point2->setType(QCPItemPosition::ptPlotCoords);
    cursor_r->point1->setType(QCPItemPosition::ptPlotCoords);
    cursor_r->point2->setType(QCPItemPosition::ptPlotCoords);
    cursor_l->setPen(QPen(QColor(0, 255, 0)));
    cursor_r->setPen(QPen(QColor(255, 0, 0)));
    ui->plotWidget->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectPlottables | QCP::iMultiSelect);
    ui->plotWidget->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->plotWidget->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->plotWidget->addGraph();
    ui->plotWidget->graph()->setLineStyle(QCPGraph::lsLine);
    ui->plotWidget->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plotWidget->graph()->setSelectable(QCP::stDataRange);

    connect(ui->plotWidget, &QCustomPlot::selectionChangedByUser, this, &MainWindow::selectionChanged);
    connect(ui->plotWidget, &QCustomPlot::mouseWheel, this, &MainWindow::mouseWheel);
    connect(ui->plotWidget, &QCustomPlot::mousePress, this, &MainWindow::graphClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadButton_clicked()
{
    int counter_x = 0;
    int y_max = INT_MIN, y_min = INT_MAX;
    data_y->clear();
    bool isOk = false;
    file = new QFile(ui->loadPathEdit->text());
    if(!file->open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error", "Failed to open the file");
        return;
    }
    while(!file->atEnd())
    {
        QString tmpString = file->readLine();
        if(tmpString != "")
        {
            int tmpInt = tmpString.toInt(&isOk);
            if(isOk)
            {
                data_x->append(counter_x);
                data_y->append(tmpInt);
                counter_x++;
                if(tmpInt > y_max)
                    y_max = tmpInt;
                if(tmpInt < y_min)
                    y_min = tmpInt;
            }
        }
    }

    ui->plotWidget->graph()->setData(*data_x, *data_y, true);
    ui->plotWidget->xAxis->setRange(0, counter_x);
    ui->plotWidget->yAxis->setRange(y_min - 10, y_max + 10);
    ui->plotWidget->replot();

}

void MainWindow::mouseWheel()
{
    ui->plotWidget->graph()->rescaleValueAxis(false, true);
}

void MainWindow::selectionChanged()
{

}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event)
{
    qDebug() << dataIndex << event;
    if(event->button() == Qt::LeftButton)
    {
        cursor_l->point1->setCoords(ui->plotWidget->graph()->dataMainKey(dataIndex), 0);
        cursor_l->point2->setCoords(ui->plotWidget->graph()->dataMainKey(dataIndex), 1);
        cursor_l->setVisible(true);
    }
    else if(event->button() == Qt::LeftButton)
    {
        cursor_r->point1->setCoords(ui->plotWidget->graph()->dataMainKey(dataIndex), 0);
        cursor_r->point2->setCoords(ui->plotWidget->graph()->dataMainKey(dataIndex), 1);
        cursor_r->setVisible(true);
    }

}
