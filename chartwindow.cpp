#include "chartwindow.h"

ChartWindow::ChartWindow(QStandardItemModel *data, QWidget *parent): QWidget{parent}
{
    dataBase = new QStandardItemModel;
    dataBase = data;
    setFixedSize(700, 500);
}

void ChartWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    short indent = 50, end_Oy_x = indent, end_Oy_y = indent, // indent - отступ от оси
        end_Ox_x = width()-indent, end_Ox_y = height()-indent,
        begin_x = indent, begin_y = height()-indent;
    painter.begin(this);

    QPen pen;
    pen.setWidth(2); // Толщина пера 2 пикселя
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(QColorConstants::Black); // Черный цвет заливки
    brush.setStyle(Qt::SolidPattern); // Сплошная заливка
    painter.setBrush(brush);

    QFont font("Arial", 15); // Тип шрифта
    painter.setFont(font);

    // Создание осей координат
    painter.drawLine(begin_x, begin_y, end_Ox_x, end_Ox_y); // OX
    painter.drawLine(begin_x, begin_y, end_Oy_x, end_Oy_y); // OY
    // Стрелки
    QPolygon arrowOy, arrowOx;
    arrowOy << QPoint(end_Oy_x, end_Oy_y) << QPoint(end_Oy_x - 5, end_Oy_y + 20)
            << QPoint(end_Oy_x, end_Oy_y+10) <<  QPoint(end_Oy_x + 5, end_Oy_y + 20); // Стрелка Oy
    painter.drawPolygon(arrowOy);

    arrowOx << QPoint(end_Ox_x, end_Ox_y) << QPoint(end_Ox_x - 20, end_Ox_y - 5)
            << QPoint(end_Ox_x - 10, end_Ox_y) << QPoint(end_Ox_x - 20, end_Ox_y + 5); // Стрелка Ox
    painter.drawPolygon(arrowOx);

    painter.drawText(begin_x-19, begin_y+19, "0");
    painter.drawText(end_Ox_x + 4, end_Ox_y + 5, "Номер");
    painter.drawText(end_Oy_x - 48, end_Oy_y - 4, "Атомная масса (а.е.м.)");
    int maxNumber = 0, minNumber = 1000;
    int maxAtomicMass = 0, minAtomicMass = 1000;
    for (int i = 0; i < dataBase->rowCount(); i++){ // Поиск максимальный и минимальных номеров и масс в моделе
        maxNumber = std::max(maxNumber, dataBase->item(i, 0)->text().toInt());
        minNumber = std::min(minNumber, dataBase->item(i, 0)->text().toInt());
        maxAtomicMass = std::max(maxAtomicMass, int(dataBase->item(i, 2)->text().toDouble() + 0.5));
        minAtomicMass = std::min(minAtomicMass, int(dataBase->item(i, 2)->text().toDouble() + 0.5));
    }

    short singleOX = std::max(30, (end_Ox_x - 40 - begin_x)/(maxNumber-minNumber)),
        countLinesOX = std::min((end_Ox_x - 40 - begin_x) / singleOX, maxNumber - minNumber);
    short numberIncreaseByLineOX, firstValueOX;
    if (((maxNumber-minNumber) / countLinesOX + 0.99) > (short)minNumber){
        numberIncreaseByLineOX = short(double(maxNumber-minNumber) / countLinesOX + 0.99);
        firstValueOX = numberIncreaseByLineOX;
    }
    else{
        firstValueOX = minNumber;
        numberIncreaseByLineOX = short(double(maxNumber-minNumber) / (countLinesOX - 1) + 0.99);
    }
    for (short i = 1, ind = firstValueOX; i <= countLinesOX; i++, ind += numberIncreaseByLineOX){
        painter.drawLine(begin_x + i * singleOX, begin_y + 5, begin_x + i * singleOX, begin_y-5);
        painter.drawText(begin_x + i * singleOX - 4 * (int(ind >= 100) + int(ind >= 10) + 1), begin_y + 20, QString::number(ind));
    }

    short singleOY = std::max(25, (-end_Oy_y - 30 + begin_y)/(maxAtomicMass-minAtomicMass)),
        countLinesOY = std::min((-end_Oy_y - 30 + begin_y) / singleOY, maxAtomicMass - minAtomicMass);

    short MassIncreaseByLineOY, firstValueOY;
    if (double(maxAtomicMass-minAtomicMass) / countLinesOY + 0.99 > (short)minAtomicMass){
        MassIncreaseByLineOY = double(maxAtomicMass-minAtomicMass) / countLinesOY + 0.99;
        firstValueOY = MassIncreaseByLineOY;
    }
    else{
        firstValueOY = (short)minAtomicMass;
        MassIncreaseByLineOY = double(maxAtomicMass-minAtomicMass) / (countLinesOY - 1) + 0.99;
    }

    for (short i = 1, ind = firstValueOY; i <= countLinesOY; i++, ind += MassIncreaseByLineOY){
        painter.drawLine(begin_x - 5, begin_y - i * singleOY, begin_x + 5, begin_y - i * singleOY);
        painter.drawText(begin_x - 16 - 5 * (int(ind >= 100) + int(ind >= 10) + 1), begin_y - i * singleOY + 6, QString::number(ind));
    }

    pen.setColor(QColorConstants::Red);
    pen.setWidth(4);
    painter.setPen(pen);
    QPolygon chart;
    for (int i = 0 ; i < dataBase->rowCount(); i++){
        chart << QPoint(begin_x + singleOX + (dataBase->item(i, 0)->text().toInt() - firstValueOX) * singleOX / numberIncreaseByLineOX,
                        begin_y - singleOY - (short(dataBase->item(i, 2)->text().toDouble()) - firstValueOY) * singleOY / MassIncreaseByLineOY);
    }
    painter.drawPolyline(chart);
    painter.end();
}
void ChartWindow::setDataBase(QStandardItemModel *data)
{
    dataBase = data;
}

ChartWindow::~ChartWindow(){};
