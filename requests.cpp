#include "requests.h"

Requests::Requests(QStandardItemModel *dataBase, QDialog *parent): QDialog{parent}
{
    setWindowTitle("Запросы");

    buttonFirstOperation = new QPushButton("Вывести названия и атомные массы всех полупроводников");
    buttonFirstOperation->setAutoDefault(false);
    buttonFirstOperation->setDefault(false);

    buttonSecondOperation = new QPushButton("Вывести проводники по возрастанию их номеров");
    buttonSecondOperation->setAutoDefault(false);
    buttonSecondOperation->setDefault(false);

    buttonThirdOperation = new QPushButton("Вывести изоляторы с атомной массой не более X");
    buttonThirdOperation->setAutoDefault(false);
    buttonThirdOperation->setDefault(false);

    lineEditThirdOperation = new QLineEdit();
    lineEditThirdOperation->setPlaceholderText("00.000");

    buttonFourthOperation = new QPushButton("Построить график зависимости атомной массы элемента от его номера");
    buttonFourthOperation->setAutoDefault(false);
    buttonFourthOperation->setDefault(false);

    buttonCloseWindow = new QPushButton("Назад");
    buttonCloseWindow->setAutoDefault(false);
    buttonCloseWindow->setDefault(false);

    MainLayout = new QVBoxLayout(this);
    HorizontalLayout = new QHBoxLayout();

    MainLayout->addWidget(buttonFirstOperation);
    MainLayout->addWidget(buttonSecondOperation);
    HorizontalLayout->addWidget(buttonThirdOperation);
    HorizontalLayout->addWidget(lineEditThirdOperation);
    MainLayout->addLayout(HorizontalLayout);
    MainLayout->addWidget(buttonFourthOperation);
    MainLayout->addWidget(buttonCloseWindow);

    infoForFirstRequest = new InfoForRequest(1, dataBase, "Запрос 1");
    infoForSecondRequest = new InfoForRequest(2, dataBase, "Запрос 2");
    infoForThirdRequest = new InfoForRequest(3, dataBase, "Запрос 3");
    infoForFourthRequest = new ChartWindow(dataBase);

    //
    connect(buttonFirstOperation, SIGNAL(clicked(bool)), infoForFirstRequest, SLOT(showInfoForRequest()));
    connect(infoForFirstRequest->buttonCloseWindow, SIGNAL(clicked(bool)), infoForFirstRequest, SLOT(closeInfoForRequest()));

    connect(buttonSecondOperation, SIGNAL(clicked(bool)), infoForSecondRequest, SLOT(showInfoForRequest()));
    connect(infoForSecondRequest->buttonCloseWindow, SIGNAL(clicked(bool)), infoForSecondRequest, SLOT(closeInfoForRequest()));

    connect(lineEditThirdOperation, SIGNAL(editingFinished()), this, SLOT(showInfoForThirdRequest()));
    connect(buttonThirdOperation, SIGNAL(clicked(bool)), this, SLOT(showInfoForThirdRequest()));
    connect(infoForThirdRequest->buttonCloseWindow, SIGNAL(clicked(bool)), infoForThirdRequest, SLOT(closeInfoForRequest()));

    connect(buttonFourthOperation, SIGNAL(clicked(bool)), infoForFourthRequest, SLOT(show()));
}

void Requests::showInfoForThirdRequest(){
    infoForThirdRequest->showInfoForRequest(lineEditThirdOperation->text().toDouble());
}

void InfoForRequest::showInfoForRequest(double value){
    valueLineEdit = value;
    this->setDataForRequest();
    this->show();
}
void InfoForRequest:: closeInfoForRequest(){
    this->close();
}


void InfoForRequest::setDataForRequest(){
    dataForRequest->clear();
    QList <QStandardItem*> bufRow;
    QString conductivityInfo;
    switch (typeOfRequest) {
    case 1:
        conductivityInfo = "Полупроводник";
        used[0] = used[3] = false;
        used[1] = used[2] = true;
        break;
    case 2:
        conductivityInfo = "Проводник";
        used[0] = used[1] = used[2] = used[3] = true;
        break;
    case 3:
        conductivityInfo = "Изолятор";
        used[0] = used[3] = false;
        used[1] = used[2] = true;
        break;
    }

    for (int i = 0; i < dataBase->rowCount(); i++){
        if (dataBase->item(i, 3)->text() != conductivityInfo) continue; // Отсеиваем элементы с неподходящей для запроса проводимостью
        if (typeOfRequest == 3 && dataBase->item(i, 2)->text().toDouble() > valueLineEdit) continue; // В случае запроса 3 элементы фильтруются также по атомной массе
        for (int j = 0; j < 4; j++){
            if (!used[j]) continue;
            bufRow.append(new QStandardItem(dataBase->item(i, j)->text()));
        }
        dataForRequest->appendRow(bufRow);
        bufRow.clear();
    }

    QString headers[4] = {"Номер элемента \nв таблице Менделеева", "Название элемента", "Относительная \nатомная масса", " Проводимость "};
    for (int i = 0, j = 0; i < 4; i++){
        if (used[i]) dataForRequest->setHeaderData(j++, Qt::Horizontal, headers[i]);
    }

    if (typeOfRequest == 2){
        dataForRequest->sort(0);
    }

    table->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирования таблицы
    table->setSelectionMode(QAbstractItemView::SingleSelection); // Единичный выбор элемента в таблице
    table->setSelectionBehavior(QAbstractItemView::SelectRows); // Выбор только строк

    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    labelSearch->setText("Найдено результатов: " + QString::number(dataForRequest->rowCount()) + " шт.");

}

InfoForRequest::InfoForRequest(short type, QStandardItemModel *data, QString title, QDialog *parent): QDialog{parent}{
    typeOfRequest = type;
    dataBase = data;
    setWindowTitle(title);
    labelSearch = new QLabel();
    dataForRequest = new QStandardItemModel();
    table = new QTableView;
    table->setModel(dataForRequest);
    setDataForRequest();

    setMinimumWidth(150*(short(used[0]) + short(used[1]) + short(used[2]) + short(used[3])));

    buttonCloseWindow = new QPushButton("Назад");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(labelSearch);
    mainLayout->addWidget(table);
    mainLayout->addWidget(buttonCloseWindow);

}


InfoForRequest::~InfoForRequest(){};
Requests::~Requests(){};
