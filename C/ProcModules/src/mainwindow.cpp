#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "procutil.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

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
    auto procList = ProcUtil::GetProcessList();
    ui->Proc_procWidget->clearContents();
    ui->Proc_procWidget->setRowCount(procList.size());
    for(int i = 0; i < procList.size(); i++)
    {
        auto tmp = new QTableWidgetItem;
        tmp->setData(Qt::EditRole, procList[i].PID); // for sort
        ui->Proc_procWidget->setItem(i, 0, tmp);
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

void MainWindow::applyModFilter()
{
    const QString filter = ui->Mod_filterEdit->text();
    if(filter.isEmpty())
    {
        for(int i = 0; i < ui->Mod_modWidget->count(); i++)
        {
            ui->Mod_modWidget->setRowHidden(i, false);
        }
    }
    else
    {
        for(int i = 0; i < ui->Mod_modWidget->count(); i++)
        {
            ui->Mod_modWidget->setRowHidden(i, !ui->Mod_modWidget->item(i)->text().contains(filter, Qt::CaseInsensitive));
        }
    }
}

void MainWindow::on_Proc_filterEdit_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    applyProcFilter();
}


void MainWindow::on_Proc_procWidget_cellClicked(int row, int column)
{
    Q_UNUSED(column)
    updateModuleList(ui->Proc_procWidget->item(row, 0)->text().toUInt());
}

void MainWindow::updateModuleList(quint32 PID)
{
    auto modList = ProcUtil::ListProcessModules(PID);
    ui->Mod_modWidget->clear();

    if(modList.size() == 0)
    {
        ui->Mod_numLabel->setText(tr("Module:"));
        ui->Mod_modWidget->setSelectionMode(QListWidget::NoSelection);
        QListWidgetItem* tmp = new QListWidgetItem(tr("<Cannot load modules>"));
        tmp->setFlags(tmp->flags().setFlag(Qt::ItemIsUserCheckable, false));
        ui->Mod_modWidget->addItem(tmp);
    }
    else
    {
        ui->Mod_numLabel->setText(tr("Module:") + QString::number(modList.size()));
        ui->Mod_modWidget->setSelectionMode(QListWidget::ExtendedSelection);
        for(int i = 0; i < modList.size(); i++)
        {
            QListWidgetItem* tmp = new QListWidgetItem(modList[i]);
            tmp->setFlags(tmp->flags() | Qt::ItemIsUserCheckable);
            tmp->setCheckState(Qt::Unchecked);
            ui->Mod_modWidget->addItem(tmp);
        }
    }

}

bool MainWindow::isModInvalid()
{
    return (ui->Mod_modWidget->count() == 1 && !ui->Mod_modWidget->item(0)->flags().testFlag(Qt::ItemIsUserCheckable));
}

void MainWindow::on_Mod_allBox_clicked(bool checked)
{
    if(isModInvalid())
    {
        ui->Mod_allBox->setChecked(false);
        return;
    }
    for(int i = 0; i < ui->Mod_modWidget->count(); i++)
    {
        if(!ui->Mod_modWidget->item(i)->isHidden())
            ui->Mod_modWidget->item(i)->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
    }
}


void MainWindow::on_Mod_highlightedBox_clicked(bool checked)
{
    if(isModInvalid())
    {
        ui->Mod_allBox->setChecked(false);
        return;
    }
    auto highlighted = ui->Mod_modWidget->selectedItems();
    for(auto it = highlighted.begin(); it != highlighted.end(); ++it)
    {
        if(!(*it)->isHidden())
            (*it)->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
    }
}


void MainWindow::on_Mod_modWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(isModInvalid())
        return;
    system(("explorer /select,\"" + item->text() + "\"").toLocal8Bit().data());
}


void MainWindow::on_Mod_exportButton_clicked()
{
    if(isModInvalid())
        return;
    QString outputDir = QFileDialog::getExistingDirectory(this, tr("Target directory to copy to"));
    if(outputDir.isEmpty())
        return;
    QString srcPath, srcName;
    int counter = 0;
    for(int i = 0; i < ui->Mod_modWidget->count(); i++)
    {
        auto tmp = ui->Mod_modWidget->item(i);
        if(tmp->isHidden() || tmp->checkState() != Qt::Checked)
            continue;
        srcPath = tmp->text();
        srcName = srcPath.split('\\').last();
        qDebug() << srcPath << outputDir + "/" + srcName;
        if(QFile::copy(srcPath, outputDir + "/" + srcName))
            counter++;
    }
    QMessageBox::information(this, tr("Info"), tr("Copied ") + QString::number(counter) + tr(" file(s)"));
}

void MainWindow::on_Mod_filterEdit_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    applyModFilter();
}


