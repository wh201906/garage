#ifndef SQLDATAWIDGET_H
#define SQLDATAWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui
{
class SqlDataWidget;
}

class SqlDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SqlDataWidget(QWidget *parent = nullptr);
    ~SqlDataWidget();

    void setDatabase(QSqlDatabase *database);
    void setTable(const QString &name);
public slots:
    void on_loadButton_clicked();
private:
    Ui::SqlDataWidget *ui;
    QSqlDatabase* database;
    QSqlTableModel *model;

    void output(const QString& msg);
private slots:
    void on_addButton_clicked();
    void on_revertButton_clicked();
    void on_submitButton_clicked();
    void on_deleteButton_clicked();
signals:
    void newOutput(const QString& msg);
};

#endif // SQLDATAWIDGET_H
