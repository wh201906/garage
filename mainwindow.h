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

    void on_student_loadButton_clicked();

    void on_student_addButton_clicked();

    void on_student_revertButton_clicked();

    void on_student_submitButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase database;

    QSqlTableModel *studentModel;
    void output(const QString &msg);
};
#endif // MAINWINDOW_H
