#ifndef REQUESTS_H
#define REQUESTS_H

#include "database.h"
#include "chartwindow.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QLineEdit>
#include <QHeaderView>
#include <QLabel>

class InfoForRequest : public QDialog
{
    Q_OBJECT

public:
    short typeOfRequest;
    double valueLineEdit = 0;
    bool used[4];
    QStandardItemModel *dataBase, *dataForRequest;
    QTableView *table;
    QPushButton *buttonCloseWindow;
    QLabel *labelSearch;
    InfoForRequest(short typeOf, QStandardItemModel *dataBase, QString title, QDialog *parent = nullptr);
    ~InfoForRequest();

    void setDataForRequest();
public slots:
    void showInfoForRequest(double value = 0);
    void closeInfoForRequest();

};

class Requests : public QDialog
{
    Q_OBJECT

public:
    InfoForRequest *infoForFirstRequest, *infoForSecondRequest, *infoForThirdRequest;
    QStandardItemModel *dataBase;
    QLineEdit *lineEditThirdOperation;
    ChartWindow *infoForFourthRequest;
    QVBoxLayout *MainLayout;
    QHBoxLayout *HorizontalLayout;
    QPushButton *buttonCloseWindow, *buttonFirstOperation, *buttonSecondOperation, *buttonThirdOperation, *buttonFourthOperation;

    Requests(QStandardItemModel *dataBase, QDialog *parent = nullptr);
    ~Requests();


public slots:
    void showInfoForThirdRequest();
};

#endif // REQUESTS_H
