#ifndef SQLDATAWIDGET_H
#define SQLDATAWIDGET_H

#include <QWidget>
#include <QSqlDatabase>

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
private:
    Ui::SqlDataWidget *ui;
    QSqlDatabase* database;
signals:
    void output(const QString& msg);
};

#endif // SQLDATAWIDGET_H
