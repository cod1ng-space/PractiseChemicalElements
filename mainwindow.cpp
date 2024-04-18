#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    setWindowTitle("Главное меню программы 'Химические элементы'"); // Заголовок окна
    setStyle(QStyleFactory::create("Fusion"));
    // Создание кнопок
    buttonToRequests = new QPushButton("Создать запрос");
    buttonToRequests->setAutoDefault(false);
    buttonToRequests->setDefault(false);

    buttonAdd = new QPushButton("Добавить элемент");
    buttonAdd->setAutoDefault(false);
    buttonAdd->setDefault(false);

    buttonDelete = new QPushButton("Удалить элемент");
    buttonDelete->setAutoDefault(false);
    buttonDelete->setDefault(false);
    buttonDelete->setEnabled(false);

    buttonInformation = new QPushButton("Справка");
    buttonInformation->setAutoDefault(false);
    buttonInformation->setDefault(false);

    buttonEndProgramm = new QPushButton("Завершить программу");
    buttonEndProgramm->setAutoDefault(false);
    buttonEndProgramm->setDefault(false);

    table = new QTableView;
    dataBase = CreateDataBase();
    table->setModel(dataBase);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирования таблицы
    table->setSelectionMode(QAbstractItemView::SingleSelection); // Единичный выбор элемента в таблице
    table->setSelectionBehavior(QAbstractItemView::SelectRows); // Выбор только строк

    // table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Разрешение редактирования ширины столбов
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); // Запрет редактирования высоты строк


    MainLayout = new QVBoxLayout(this);
    UpperLayout = new QHBoxLayout();
    LowerLayout = new QHBoxLayout();

    UpperLayout->addWidget(buttonToRequests);
    UpperLayout->addWidget(buttonAdd);
    UpperLayout->addWidget(buttonDelete);
    UpperLayout->addSpacing(150);
    UpperLayout->addStretch();
    UpperLayout->addWidget(buttonInformation);

    LowerLayout->addStretch();
    LowerLayout->addWidget(buttonEndProgramm);

    MainLayout->addLayout(UpperLayout);
    MainLayout->addWidget(table);
    MainLayout->addLayout(LowerLayout);

    requestWindow = new Requests(dataBase);
    addWindow = new AddElement;
    connect(buttonEndProgramm, SIGNAL(clicked(bool)), this, SLOT(EndProgramm()));

    connect(buttonToRequests, SIGNAL(clicked(bool)), this, SLOT(showRequestsWindow()));
    connect(requestWindow->buttonCloseWindow, SIGNAL(clicked(bool)), this, SLOT(closeRequestsWindow()));
    connect(requestWindow, SIGNAL(rejected()), this, SLOT(closeRequestsWindow()));

    connect(buttonInformation, SIGNAL(clicked(bool)), this, SLOT(InformationMessage()));

    connect(buttonAdd, SIGNAL(clicked(bool)), this, SLOT(showAddElementWindow()));
    connect(addWindow->buttonCloseWindow, SIGNAL(clicked(bool)), this, SLOT(closeAddElementWindow()));
    connect(addWindow, SIGNAL(rejected()), this, SLOT(closeAddElementWindow()));
    connect(addWindow->buttonSaveInfo, SIGNAL(clicked(bool)), this, SLOT(saveElement()));

    connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(rowSelected(QModelIndex)));
    connect(buttonDelete, SIGNAL(clicked(bool)), this, SLOT(deleteElement()));
}

void MainWindow::showRequestsWindow(){
    setEnabled(false);
    requestWindow->show();
}

void MainWindow::closeRequestsWindow(){
    setEnabled(true);
    requestWindow->hide();
}

void MainWindow::showAddElementWindow(){
    setEnabled(false);
    addWindow->show();
}

void MainWindow::closeAddElementWindow(){
    setEnabled(true);
    addWindow->clearFields();
    addWindow->close();
}

void MainWindow::saveElement(){
    AddElementToDataBase(dataBase, addWindow->number->text().toInt(),
                         addWindow->name->text(),
                         addWindow->atomicMass->text().toDouble(),
                         addWindow->conductivity->text());
    setEnabled(true);
    addWindow->clearFields();
    addWindow->close();
}

void MainWindow::rowSelected(QModelIndex index){
    buttonDelete->setEnabled(true);
    selectedRow = index.row();
}

void MainWindow::deleteElement(){
    dataBase->removeRow(selectedRow);
    if (selectedRow >= dataBase->rowCount()){
        if (selectedRow != 0) selectedRow--;
        else {
            buttonDelete->setEnabled(false);
        }
    }

}

void MainWindow::InformationMessage(){
    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::NoIcon); // Тип окна
    msgBox.setText("Справка");
    msgBox.setInformativeText("Программа содержит информацию о химических элементах из таблицы Менделеева и может выполнять следующие операции:\n"
                              " 1) Добавить химический элемент;\n"
                              " 2) Удалить существующий химический элемент;\n"
                              " 3) Найти названия и атомные массы всех полупроводников;\n"
                              " 4) Вывести сведения о проводниках в порядке возрастания их номеров;\n"
                              " 5) Определить названия всех изоляторов, атомная масса которых не превышают заданного значения;\n"
                              " 6) Построить график зависимости атомной массы элемента от его номера.");
    QPushButton *buttonMSGBoxExit = msgBox.addButton("Назад", QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() == buttonMSGBoxExit)
        msgBox.close();

}

void MainWindow::EndProgramm(){
    //SaveDataBase(dataBase);
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event){
    //SaveDataBase(dataBase);
    this->close();
}

MainWindow::~MainWindow() {}
