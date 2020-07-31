#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QSpinBox;
class QLineEdit;
class FMNineCell;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sltSetValueToCell();
    void sltSelectPic();
    void sltExport();

private:
    QPushButton *btnStart = nullptr,*btnExport = nullptr;
    QSpinBox *rowEdit = nullptr, *colEdit = nullptr;
    QLineEdit *picEdit = nullptr;
    FMNineCell *nineCell = nullptr;
};

#endif // MAINWINDOW_H
