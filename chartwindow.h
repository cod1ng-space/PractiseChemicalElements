#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QStandardItemModel>

class ChartWindow : public QWidget
{
    Q_OBJECT
public:
    QStandardItemModel *dataBase;
    ChartWindow(QStandardItemModel *data, QWidget *parent = nullptr);
    ~ChartWindow();
    void paintEvent(QPaintEvent*) override;
    void setDataBase(QStandardItemModel *data);
signals:
};

#endif // CHARTWINDOW_H
