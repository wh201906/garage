#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sqldatawidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("QODBC");
    ((QVBoxLayout*)ui->centralwidget->layout())->setStretch(0, 3); // tabWidget
    ((QVBoxLayout*)ui->centralwidget->layout())->setStretch(1, 1); // stateEdit
    queryModel = new QSqlQueryModel;
    ui->query_queryView->setModel(queryModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_conn_openButton_clicked()
{
    QString dsn;
    if(database.isOpen())
    {
        output("Database is already opened.");
        return;
    }
    // setHostname() and setPort doesn't work

    dsn += "Driver={SQL Server};";
    dsn += "Server=" + ui->conn_hostnameEdit->text() + "," + ui->conn_portEdit->text() + ";";
    dsn += "Database=" + ui->conn_databaseNameEdit->text() + ";";
    database.setUserName(ui->conn_usernameEdit->text());
    database.setPassword(ui->conn_passwordEdit->text());
    database.setDatabaseName(dsn);
    output("Connecting...");
    if(database.open())
    {
        output("Database opened.");
        createTables();

    }
    else
    {
        output("Failed to open database!");
        output("Error:" + database.lastError().text());
    }
}

void MainWindow::on_conn_closeButton_clicked()
{

    if(database.isOpen())
    {
        int num = ui->tabWidget->count();
        database.close();
        for(int i = 2; i < num; i++)
            removeTable(2); //always remove the third tab
        output("Database closed.");
    }
    else
    {
        output("Database is not open!");
    }
}

void MainWindow::output(const QString& msg)
{
    ui->stateEdit->appendPlainText(msg);
    QApplication::processEvents();
}

void MainWindow::on_conn_showPasswordBox_clicked(bool checked)
{
    if(checked)
        ui->conn_passwordEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->conn_passwordEdit->setEchoMode(QLineEdit::Password);
}

void MainWindow::createTables()
{
    QStringList tableList = database.tables();
    for(auto it = tableList.begin(); it != tableList.end(); it++)
    {
        SqlDataWidget* w = new SqlDataWidget;
        connect(w, &SqlDataWidget::newOutput, this, &MainWindow::output);
        w->setDatabase(&database);
        w->setTable(*it);
        w->on_loadButton_clicked();
        ui->tabWidget->addTab(w, *it);
    }
}

void MainWindow::removeTable(int index)
{
    QWidget* w;
    w = ui->tabWidget->widget(index);
    if(w != nullptr)
    {
        delete w;
        ui->tabWidget->removeTab(index);
    }
}

void MainWindow::on_query_execButton_clicked()
{
    QSqlError err;
    queryModel->setQuery(ui->query_queryEdit->toPlainText());
    err = queryModel->lastError();
    if(err.isValid())
    {
        output("Error:" + err.text());
    }
    else
    {
        output("Query executed");
    }
}

