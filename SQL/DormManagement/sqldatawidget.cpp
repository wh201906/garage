#include "sqldatawidget.h"
#include "ui_sqldatawidget.h"

#include <QSqlError>

SqlDataWidget::SqlDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlDataWidget)
{
    ui->setupUi(this);
    model = new QSqlTableModel;
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

SqlDataWidget::~SqlDataWidget()
{
    delete ui;
}

void SqlDataWidget::setDatabase(QSqlDatabase* database)
{
    this->database = database;
}

void SqlDataWidget::setTable(const QString& name)
{
    model->setTable(name);
}

void SqlDataWidget::on_loadButton_clicked()
{
    model->select();
    ui->tableView->setModel(model);
}


void SqlDataWidget::on_addButton_clicked()
{
    model->insertRow(model->rowCount());
}


void SqlDataWidget::on_revertButton_clicked()
{
    model->revertAll();
}


void SqlDataWidget::on_submitButton_clicked()
{
    output("Submitting...");
    database->transaction();
    if(model->submitAll())
    {
        database->commit();
        output("Submitted");
    }
    else
    {
        database->rollback();
        output("Failed to submit!");
        output("Error:" + model->lastError().text());
    }
}

void SqlDataWidget::output(const QString& msg)
{
    emit newOutput(msg);
}

void SqlDataWidget::on_deleteButton_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if(select->hasSelection())
    {
        QModelIndexList rows = select->selectedRows();
        for(auto it = rows.begin(); it != rows.end(); it++)
        {
            model->removeRow(it->row());
        }
    }
}

