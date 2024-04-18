#include "addelement.h"

AddElement::AddElement(QDialog *parent): QDialog{parent}
{
    setWindowTitle("Добавление элемента");


    labelName = new QLabel("Название элемента");
    name = new QLineEdit(this);
    name->setPlaceholderText("Углерод");

    labelNumber = new QLabel("Атомный номер");
    number = new QLineEdit(this);
    number->setPlaceholderText("6");

    labelAtomicMass = new QLabel("Атомная масса");
    atomicMass = new QLineEdit(this);
    atomicMass->setPlaceholderText("12.0096");

    labelConductivity = new QLabel("Проводимость");
    conductivity = new QLineEdit(this);
    conductivity->setPlaceholderText("Полупроводник");

    QGridLayout *averageLayout = new QGridLayout();
    averageLayout->addWidget(labelName, 0, 0);
    averageLayout->addWidget(name, 0, 1);
    averageLayout->addWidget(labelNumber, 1, 0);
    averageLayout->addWidget(number, 1, 1);
    averageLayout->addWidget(labelAtomicMass, 2, 0);
    averageLayout->addWidget(atomicMass, 2, 1);
    averageLayout->addWidget(labelConductivity, 3, 0);
    averageLayout->addWidget(conductivity, 3, 1);

    buttonCloseWindow = new QPushButton("Назад");
    buttonCloseWindow->setAutoDefault(false);
    buttonCloseWindow->setDefault(false);

    buttonSaveInfo = new QPushButton("Сохранить");

    lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(buttonSaveInfo);
    lowerLayout->addWidget(buttonCloseWindow);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(averageLayout);
    mainLayout->addLayout(lowerLayout);

}

void AddElement::clearFields(){
    this->atomicMass->clear();
    this->name->clear();
    this->conductivity->clear();
    this->number->clear();
    return;
}

AddElement::~AddElement(){};
