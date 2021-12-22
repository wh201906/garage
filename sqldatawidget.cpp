#include "sqldatawidget.h"
#include "ui_sqldatawidget.h"

SqlDataWidget::SqlDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlDataWidget)
{
    ui->setupUi(this);
}

SqlDataWidget::~SqlDataWidget()
{
    delete ui;
}

void SqlDataWidget::setDatabase(QSqlDatabase* database)
{
    this->database = database;
}
