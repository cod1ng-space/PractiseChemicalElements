#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "requests.h"
#include "addelement.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>
#include <QStyleFactory>

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *buttonToRequests, *buttonAdd, *buttonDelete, *buttonEndProgramm, *buttonInformation;
    Requests *requestWindow;
    AddElement *addWindow;
    QTableView *table;
    QStandardItemModel *dataBase;
    QVBoxLayout *MainLayout;
    QHBoxLayout *UpperLayout, *LowerLayout;
    int selectedRow;

private slots:
    void showRequestsWindow();
    void closeRequestsWindow();
    void InformationMessage();
    void showAddElementWindow();
    void closeAddElementWindow();
    void saveElement();
    void rowSelected(QModelIndex index);
    void deleteElement();
    void EndProgramm();
    void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H
