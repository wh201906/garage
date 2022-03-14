#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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
    void on_Proc_updateButton_clicked();

    void on_Proc_filterEdit_textEdited(const QString &arg1);

    void on_Proc_procWidget_cellClicked(int row, int column);

    void on_Mod_allBox_clicked(bool checked);

    void on_Mod_highlightedBox_clicked(bool checked);

    void on_Mod_modWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_Mod_exportButton_clicked();

    void on_Mod_filterEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void applyProcFilter();
    void applyModFilter();
    void updateModuleList(quint32 PID);
    bool isModInvalid();
};
#endif // MAINWINDOW_H
