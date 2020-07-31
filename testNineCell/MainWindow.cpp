#include "MainWindow.h"

#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>

#include "FMNineCell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto cent = new QWidget(this);
    auto vlay = new QVBoxLayout(cent);
    auto hlay = new QHBoxLayout();
    cent->setLayout(vlay);
    setCentralWidget(cent);

    btnStart = new QPushButton("...", this);
    btnExport = new QPushButton("导出", this);
    rowEdit = new QSpinBox(this);
    rowEdit->setRange(1,10);
    colEdit = new QSpinBox(this);
    colEdit->setRange(1,10);
    picEdit = new QLineEdit(this);
    nineCell = new FMNineCell(1,1,this);

    auto lblR = new QLabel("行数",this);
    auto lblC = new QLabel("列数",this);
    auto lblP = new QLabel("图片",this);

    hlay->addWidget(lblR);
    hlay->addWidget(rowEdit);
    hlay->addWidget(lblC);
    hlay->addWidget(colEdit);
    hlay->addWidget(lblP);
    hlay->addWidget(picEdit);
    hlay->addWidget(btnStart);
    hlay->addWidget(btnExport);

    vlay->addLayout(hlay, 1);
    vlay->addWidget(nineCell, 10);

    connect(rowEdit, SIGNAL(valueChanged(int)), this, SLOT(sltSetValueToCell()));
    connect(colEdit, SIGNAL(valueChanged(int)), this, SLOT(sltSetValueToCell()));
    connect(picEdit, &QLineEdit::textChanged, this, &MainWindow::sltSetValueToCell);
    connect(btnStart, &QPushButton::clicked, this, &MainWindow::sltSelectPic);
    connect(btnExport, &QPushButton::clicked, this, &MainWindow::sltExport);

}
MainWindow::~MainWindow()
{

}
void MainWindow::sltSetValueToCell()
{
    auto picPath = picEdit->text();
    QFile f(picPath);
    if (f.exists() == false) {
        return;
    }
    nineCell->setRowCol(rowEdit->value(), colEdit->value());
    nineCell->setPicPath(picPath);
}
void MainWindow::sltSelectPic()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择图片"),
                                                      "/",
                                                      tr("图片 (*.png *.bmp *.jpg)"));
    if (fileName.size() > 0) {
        picEdit->setText(fileName);
        QPixmap pic(fileName);
        auto picSz = pic.size();
        auto scrSz = QApplication::desktop()->screenGeometry().size();
        bool isBigW = false, isBigH = false;
        if (picSz.width() < scrSz.width()) {
            this->setMinimumWidth(picSz.width());
        } else {
            isBigW = true;
        }
        if (picSz.height() < scrSz.height()) {
            this->setMinimumHeight(picSz.height());
        } else {
            isBigH = true;
        }
        if (isBigH || isBigW) {
            showMaximized();
        }

    }
}
void MainWindow::sltExport()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出图片"),
                                 "/untitled.png",
                                 tr("图片 (*.png *.jpg)"));
    if (fileName.size() > 0) {
        nineCell->exprotPic(fileName);
    }
}
