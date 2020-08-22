#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <qcustomplot.h>
#include <QDebug>

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
    void on_loadButton_clicked();

    void mouseWheel();
    void selectionChanged();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
    void on_deleteSelectedButton_clicked();

    void on_deleteUnselectedButton_clicked();

    void on_barValueChanged(int val);
    void on_axisRangeChanged(const QCPRange &range);
    void on_insertButton_clicked();

    void on_loadPathEdit_returnPressed();

    void on_savePathEdit_returnPressed();

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double>* data_x;
    QVector<double>* data_y;
    QFile* file;
    QCPItemStraightLine* cursor_l;
    QCPItemStraightLine* cursor_r;
    void myResizeYAxis();
    void myResizeXAxis();
};
#endif // MAINWINDOW_H
