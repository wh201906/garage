#include "mainwindow.h"
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
    connect(ui->plotWidget, &QCustomPlot::plottableClick, this, &MainWindow::graphClicked);
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
    QCPDataSelection selection = ui->plotWidget->graph()->selection();
    if(selection.dataPointCount() > 1)
    {
        int begin = selection.dataRange().begin();
        int end = selection.dataRange().end();
        ui->selectionLabel->setText(QString("(%1, %2)").arg(begin).arg(end));
        cursor_l->point1->setCoords(begin, 0);
        cursor_l->point2->setCoords(begin, 1);
        cursor_l->setVisible(true);
        cursor_r->point1->setCoords(end, 0);
        cursor_r->point2->setCoords(end, 1);
        cursor_r->setVisible(true);
    }
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event)
{
    qDebug() << dataIndex << event << ui->plotWidget->graph()->dataMainKey(dataIndex);
    if(event->button() == Qt::LeftButton)
    {
        cursor_l->point1->setCoords(data_x->at(dataIndex), 0);
        cursor_l->point2->setCoords(data_x->at(dataIndex), 1);
        ui->cursorL_Label->setText(QString("CursorL:(%1, %2)").arg(data_x->at(dataIndex)).arg(data_y->at(dataIndex)));
        cursor_l->setVisible(true);
    }
    else if(event->button() == Qt::RightButton)
    {
        cursor_r->point1->setCoords(data_x->at(dataIndex), 0);
        cursor_r->point2->setCoords(data_x->at(dataIndex), 1);
        ui->cursorR_Label->setText(QString("CursorR:(%1, %2)").arg(data_x->at(dataIndex)).arg(data_y->at(dataIndex)));
        cursor_r->setVisible(true);
    }
    if(ui->selectCursorArrangedBox->isChecked() && cursor_l->visible() && cursor_r->visible() && cursor_l->point1->key() != cursor_r->point1->key())
    {
        QCPDataRange range;
        if(cursor_l->point1->key() < cursor_r->point1->key())
        {
            range.setBegin(cursor_l->point1->key());
            range.setEnd(cursor_r->point1->key());
        }
        else
        {
            range.setBegin(cursor_r->point1->key());
            range.setEnd(cursor_l->point1->key());
        }
        ui->selectionLabel->setText(QString("Selected:(%1, %2)").arg(range.begin()).arg(range.end()));
        ui->plotWidget->blockSignals(true);
        ui->plotWidget->graph()->setSelection(QCPDataSelection(range));
        ui->plotWidget->blockSignals(false);
    }
    ui->plotWidget->replot(); // otherwise, the right won't respond immediately.
}

void MainWindow::on_deleteSelectedButton_clicked()
{
    QCPDataSelection selection = ui->plotWidget->graph()->selection();
    int begin = selection.dataRange().begin();
    int end = selection.dataRange().end();
    data_y->remove(begin, end - begin);
    data_x->remove(data_x->size() - (end - begin), end - begin);
    ui->plotWidget->graph()->setData(*data_x, *data_y, true);
    ui->plotWidget->graph()->setSelection(QCPDataSelection());
    cursor_l->setVisible(false);
    cursor_r->setVisible(false);
    ui->plotWidget->replot();
}

void MainWindow::on_deleteUnselectedButton_clicked()
{
    QCPDataSelection selection = ui->plotWidget->graph()->selection();
    int begin = selection.dataRange().begin();
    int end = selection.dataRange().end();
    data_y->remove(end, data_x->size() - end);
    data_y->remove(0, begin);
    data_x->remove(end - begin, data_x->size() - (end - begin));
    ui->plotWidget->graph()->setData(*data_x, *data_y, true);
    ui->plotWidget->graph()->setSelection(QCPDataSelection());
    cursor_l->setVisible(false);
    cursor_r->setVisible(false);
    ui->plotWidget->replot();
}
