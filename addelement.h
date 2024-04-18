#ifndef ADDELEMENT_H
#define ADDELEMENT_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLayout>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>

class AddElement : public QDialog
{
    Q_OBJECT
private:

    QLabel *labelName, *labelNumber, *labelConductivity, *labelAtomicMass;

public:
    AddElement(QDialog *parent = nullptr);
    ~AddElement();
    QLineEdit *name, *number, *conductivity, *atomicMass;
    QPushButton *buttonCloseWindow, *buttonSaveInfo;
    QVBoxLayout *mainLayout;
    QHBoxLayout *lowerLayout;

    void clearFields();

signals:

};
#endif // ADDELEMENT_H
