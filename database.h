#ifndef DATABASE_H
#define DATABASE_H
#include <QStandardItemModel>
#include <QList>

class ChemicalElement{
public:
    int number;
    char name[50], conductivity[20];
    double atomicMass;
};

QStandardItemModel* CreateDataBase();

void AddElementToDataBase(QStandardItemModel *dataBase, int number, QString name, double atomicMass, QString conductivity);

void SaveDataBase(QStandardItemModel *dataBase);

#endif // DATABASE_H
