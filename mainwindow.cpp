#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("QODBC");
    ((QVBoxLayout*)ui->centralwidget->layout())->setStretch(0, 3); // tabWidget
    ((QVBoxLayout*)ui->centralwidget->layout())->setStretch(1, 1); // stateEdit
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_conn_openButton_clicked()
{
    QString dsn;
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
        database.close();
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

