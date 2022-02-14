#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_conn_openButton_clicked();

    void on_conn_closeButton_clicked();

    void on_conn_showPasswordBox_clicked(bool checked);

    void output(const QString &msg);

    void removeTable(int index);
    void on_query_execButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase database;

    QSqlQueryModel *queryModel;

    void createTables();
};
#endif // MAINWINDOW_H
