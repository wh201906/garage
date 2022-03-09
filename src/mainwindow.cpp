#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "procutil.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Proc_updateButton_clicked()
{
    QVector<ProcUtil::ProcInfo> procList = ProcUtil::GetProcessList();
    ui->Proc_procWidget->clearContents();
    ui->Proc_procWidget->setRowCount(procList.size());
    for(int i = 0; i < procList.size(); i++)
    {
        ui->Proc_procWidget->setItem(i, 0, new QTableWidgetItem(QString::number(procList[i].PID)));
        ui->Proc_procWidget->setItem(i, 1, new QTableWidgetItem(procList[i].name));
    }
    applyProcFilter();
}

void MainWindow::applyProcFilter()
{
    const QString filter = ui->Proc_filterEdit->text();
    if(filter.isEmpty())
    {
        for(int i = 0; i < ui->Proc_procWidget->rowCount(); i++)
        {
            ui->Proc_procWidget->setRowHidden(i, false);
        }
    }
    else
    {
        for(int i = 0; i < ui->Proc_procWidget->rowCount(); i++)
        {
            ui->Proc_procWidget->setRowHidden(i, !ui->Proc_procWidget->item(i, 1)->text().contains(filter, Qt::CaseInsensitive));
        }
    }
}
void MainWindow::on_Proc_filterEdit_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    applyProcFilter();
}

