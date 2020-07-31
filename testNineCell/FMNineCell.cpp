#include "FMNineCell.h"

#include <QPainter>
#include <QtMath>

FMNineCell::FMNineCell(int row, int column,QWidget *parent)
    : QWidget(parent), rowCount(row), columnCount(column),curPic("")
{

}
void FMNineCell::paintEvent(QPaintEvent *event)
{
    if (curPic.size() == 0) {
        return;
    }
    QPainter p(this);

    QPixmap pix(curPic);

    auto rt = rect();
    auto singPicW = qFloor((rt.width() - picSpace*(columnCount+1)) / columnCount);
    auto singPicH = qFloor((rt.height() - picSpace*(rowCount+1)) / rowCount);

    for (int i = 0; i < rowCount; i ++) {
        for (int j = 0; j < columnCount; j ++) {
            p.drawPixmap(picSpace*(j+1)+singPicW*j, picSpace*(i+1)+singPicH*i, singPicW, singPicH, pix);
        }
    }

}
void FMNineCell::setRowCol(const int rowValue, const int colValue)
{
    rowCount = rowValue, columnCount = colValue;
    update();
}
void FMNineCell::setPicPath(const QString picPath)
{
    curPic = picPath;
    update();
}
void FMNineCell::exprotPic(const QString exportPath)
{
    auto fmt = exportPath.split(".", QString::SkipEmptyParts).last();
    this->grab().save(exportPath, fmt.toLocal8Bit(), 100);
}
