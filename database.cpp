#include "database.h"

#define MAINFILE "/Users/admin/Desktop/Laboratory_work_on_the_subject_of_Algorithmization_and_programming/Technological_practice/FirstTask/ChemicalElements/elements.bin"
// Путь к файлу

QStandardItemModel* CreateDataBase(){
    QStandardItemModel *dataBase = new QStandardItemModel(0, 4);

    dataBase->setHeaderData(0, Qt::Horizontal, "Номер элемента \nв таблице Менделеева");
    dataBase->setHeaderData(1, Qt::Horizontal, "Название элемента");
    dataBase->setHeaderData(2, Qt::Horizontal, "Относительная \nатомная масса");
    dataBase->setHeaderData(3, Qt::Horizontal, " Проводимость ");

    FILE *filePointer = fopen(MAINFILE, "rb");
    ChemicalElement buf;
    QList <QStandardItem*> bufRow;

    while (fread(&buf, sizeof(ChemicalElement), 1, filePointer) > 0){
        bufRow.append(new QStandardItem((QString::number(buf.number)).rightJustified(3, QChar(0x0C))));
        bufRow.append(new QStandardItem(QString(buf.name)));
        bufRow.append(new QStandardItem(QString::number(buf.atomicMass)));
        bufRow.append(new QStandardItem(QString(buf.conductivity)));
        dataBase->appendRow(bufRow);
        bufRow.clear();
    }
    dataBase->sort(0);
    fclose(filePointer);

    return dataBase;
}

void AddElementToDataBase(QStandardItemModel *dataBase, int number, QString name, double atomicMass, QString conductivity){
    QList <QStandardItem*> bufRow;
    bufRow.append(new QStandardItem(QString::number(number).rightJustified(3, QChar(0x0C))));
    bufRow.append(new QStandardItem(name));
    bufRow.append(new QStandardItem(QString::number(atomicMass)));
    bufRow.append(new QStandardItem(conductivity));
    dataBase->appendRow(bufRow);
    dataBase->sort(0);

}

void SaveDataBase(QStandardItemModel *dataBase){

    FILE *filePointer = fopen(MAINFILE, "wb");
    ChemicalElement buf;
    for (int i = 0; i < dataBase->rowCount(); i++){
        buf.number = dataBase->item(i, 0)->data(Qt::EditRole).toInt();
        buf.atomicMass = dataBase->item(i, 2)->data(Qt::EditRole).toDouble();
        strcpy(buf.name, dataBase->item(i, 1)->data(Qt::EditRole).toByteArray().data());
        strcpy(buf.conductivity, dataBase->item(i, 3)->data(Qt::EditRole).toByteArray().data());
        fwrite(&buf, sizeof(ChemicalElement), 1, filePointer);
    }
    fclose(filePointer);
}
