#ifndef FMNINECELL_H
#define FMNINECELL_H

#include <QWidget>

class FMNineCell : public QWidget
{
    Q_OBJECT
public:
    explicit FMNineCell(int row, int column, QWidget *parent = 0);
    void setRowCol(const int rowValue, const int colValue);
    void setPicPath(const QString picPath);
    void exprotPic(const QString exportPath);

private:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    const int picSpace = 5;
    int rowCount, columnCount;
    QString curPic;
};

#endif // FMNINECELL_H
