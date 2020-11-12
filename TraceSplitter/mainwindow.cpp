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
    ui->plotWidget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plotWidget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plotWidget->graph(0)->setSelectable(QCP::stDataRange);

    connect(ui->plotWidget, &QCustomPlot::selectionChangedByUser, this, &MainWindow::selectionChanged);
    connect(ui->plotWidget, &QCustomPlot::mouseWheel, this, &MainWindow::mouseWheel);
    connect(ui->plotWidget, &QCustomPlot::plottableClick, this, &MainWindow::graphClicked);
    connect(ui->horizontalScrollBar, &QScrollBar::valueChanged, this, &MainWindow::on_barValueChanged);
    connect(ui->plotWidget->xAxis,  QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), this, &MainWindow::on_axisRangeChanged);
    connect(ui->insert2BeginButton, &QPushButton::clicked, this, &MainWindow::on_insertButton_clicked);
    connect(ui->insert2EndButton, &QPushButton::clicked, this, &MainWindow::on_insertButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadButton_clicked()
{
    int counter_x = 0;
    data_x->clear();
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
                data_x->append(counter_x); // 0 ~ data_x->size()-1
                data_y->append(tmpInt);
                counter_x++;
            }
        }
    }
    file->close();
    delete file;
    ui->plotWidget->graph(0)->setData(*data_x, *data_y, true);
    myResizeXAxis();
    ui->plotWidget->replot();
}

void MainWindow::mouseWheel()
{
    myResizeYAxis();
}

void MainWindow::selectionChanged()
{
    QCPDataSelection selection = ui->plotWidget->graph(0)->selection();
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
    qDebug() << dataIndex << event << ui->plotWidget->graph(0)->dataMainKey(dataIndex);
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
        ui->selectionLabel->setText(QString("Selected:(%1, %2), Δ=%3").arg(range.begin()).arg(range.end()).arg(range.end() - range.begin()));
        ui->plotWidget->blockSignals(true);
        ui->plotWidget->graph(0)->setSelection(QCPDataSelection(range));
        ui->plotWidget->blockSignals(false);
    }
    ui->plotWidget->replot(); // otherwise, the right won't respond immediately.
}

void MainWindow::on_deleteSelectedButton_clicked()
{
    QCPDataSelection selection = ui->plotWidget->graph(0)->selection();
    int begin = selection.dataRange().begin();
    int end = selection.dataRange().end();
    data_y->remove(begin, end - begin);
    data_x->remove(data_x->size() - (end - begin), end - begin);
    ui->plotWidget->graph(0)->setData(*data_x, *data_y, true);
    ui->plotWidget->graph(0)->setSelection(QCPDataSelection());
    cursor_l->setVisible(false);
    cursor_r->setVisible(false);
    myResizeXAxis();
    ui->plotWidget->replot();
}

void MainWindow::on_deleteUnselectedButton_clicked()
{
    QCPDataSelection selection = ui->plotWidget->graph(0)->selection();
    int begin = selection.dataRange().begin();
    int end = selection.dataRange().end();
    data_y->remove(end, data_x->size() - end);
    data_y->remove(0, begin);
    data_x->remove(end - begin, data_x->size() - (end - begin));
    ui->plotWidget->graph(0)->setData(*data_x, *data_y, true);
    ui->plotWidget->graph(0)->setSelection(QCPDataSelection());
    cursor_l->setVisible(false);
    cursor_r->setVisible(false);
    myResizeXAxis();
    ui->plotWidget->replot();
}

void MainWindow::on_barValueChanged(int val)
{
    ui->plotWidget->xAxis->setRange(val / 100.0 - 1, ui->horizontalScrollBar->pageStep() / 100, Qt::AlignLeft);
    myResizeYAxis();
    ui->plotWidget->replot();
}

void MainWindow::on_axisRangeChanged(const QCPRange &range)
{
    ui->horizontalScrollBar->blockSignals(true);
    ui->plotWidget->xAxis->blockSignals(true);
    QCPRange targetRange = range;
    if(targetRange.lower < -1)
        targetRange.lower = -1;
    if(targetRange.upper > data_x->size() + 1)
        targetRange.upper = data_x->size() + 1;
    ui->plotWidget->xAxis->setRange(targetRange);
    ui->horizontalScrollBar->setValue(qRound(targetRange.lower * 100.0));
    ui->horizontalScrollBar->setPageStep(qRound((targetRange.size() + 2) * 100.0));
    myResizeYAxis();
    ui->horizontalScrollBar->blockSignals(false);
    ui->plotWidget->xAxis->blockSignals(false);
}

void MainWindow::on_insertButton_clicked()
{
    QVector<double> tmp_y;
    int counter_x = 0;
    //data_y->clear();
    bool isOk = false;
    file = new QFile(ui->insertPathEdit->text());
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
                tmp_y.append(tmpInt);
                counter_x++;
            }
        }
    }
    file->close();
    delete file;
    if(qobject_cast<QPushButton *>(sender()) == ui->insert2BeginButton)
    {
        qDebug() << "insert2begin";
        *data_y = tmp_y + (*data_y);
    }
    else
    {
        qDebug() << "insert2end";
        *data_y += tmp_y;
    }
    counter_x += data_x->size();
    for(int i = data_x->size(); i < counter_x; i++)
        data_x->append(i);
    ui->plotWidget->graph(0)->setData(*data_x, *data_y, true);
    myResizeXAxis();
    ui->plotWidget->replot();
}

void MainWindow::myResizeXAxis()
{
    ui->plotWidget->xAxis->setRange(-1, data_x->size() + 1);
    ui->horizontalScrollBar->setRange(-100, (data_x->size() + 1) * 100);
    ui->horizontalScrollBar->setPageStep((data_x->size() + 2) * 100);
}

void MainWindow::myResizeYAxis()
{
    int y_min = INT_MAX, y_max = INT_MIN, tmp;
    for(int i = ui->plotWidget->xAxis->range().lower; i <= ui->plotWidget->xAxis->range().upper; i++)
    {
        if(i < 0 || i >= data_y->size())
            continue;
        tmp = ui->plotWidget->graph(0)->dataMainValue(i);
        if(tmp > y_max)
            y_max = tmp;
        if(tmp < y_min)
            y_min = tmp;
    }
    double delta = (y_max - y_min) * 0.05; // 5% margin, the rescaleValueAxis() has no margin and make it hard to choose the min/max point.
    ui->plotWidget->yAxis->setRange(y_min - delta, y_max + delta);
}

void MainWindow::on_saveButton_clicked()
{
    file = new QFile(ui->savePathEdit->text());
    if(file->exists())
    {
        QMessageBox::StandardButton result = QMessageBox::information(this, "Info", "File already exists.\nReplace it?", QMessageBox::Yes | QMessageBox::No);
        if(result != QMessageBox::Yes)
            return;
    }
    if(!file->open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
    {
        QMessageBox::information(this, "Error", "Failed to open the file");
        return;
    }
    for(double item : *data_y)
    {
        int tmpInt = qRound(item);
        qDebug() << file->write((QString::number(tmpInt) + "\n").toLocal8Bit());
    }
    file->close();
    delete file;
    QMessageBox::information(this, "Info", "Saved");
}
void MainWindow::on_loadPathEdit_returnPressed()
{
    on_loadButton_clicked();
}

void MainWindow::on_savePathEdit_returnPressed()
{
    on_saveButton_clicked();
}


void MainWindow::on_PIE_autoRangeButton_clicked()
{
    QVector<double> data_zero;
    for(int i = 1; i < data_x->size(); i++)
    {
        if(data_y->at(i - 1)*data_y->at(i) <= 0)
        {
            double a = qAbs(data_y->at(i - 1)), b = qAbs(data_y->at(i));
            double delta = a / (a + b);
            data_zero += i - 1 + delta;
        }
    }
    double int_min = data_zero.last() - data_zero.first(), int_max = 0;
    for(int i = 1; i < data_zero.size(); i++)
    {

    }
}
