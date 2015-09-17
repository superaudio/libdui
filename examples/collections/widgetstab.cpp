#include "widgetstab.h"

#include <QCheckBox>

WidgetsTab::WidgetsTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("WidgetsTab {background-color:#252627;} QCheckBox {color:#666;}");

    DUI::DCalendar *calendar = new DUI::DCalendar(this);
    calendar->setFixedSize(300, 300);
    calendar->move(8, 8);
//    calendar->setLunarFestivalHighlight(false);

    QCheckBox *lunarVisible = new QCheckBox(this);
    lunarVisible->setText("lunar visible");
    lunarVisible->move(320, 50);
    lunarVisible->setChecked(true);
    QCheckBox *festivalHighlight = new QCheckBox(this);
    festivalHighlight->setText("lunar festival highlight");
    festivalHighlight->setChecked(true);
    festivalHighlight->move(320, 80);
    QCheckBox *cellSelectable = new QCheckBox(this);
    cellSelectable->setText("cell selectable");
    cellSelectable->setChecked(true);
    cellSelectable->move(320, 110);
    QCheckBox *controlPanelVisible = new QCheckBox(this);
    controlPanelVisible->setText("control panel visible");
    controlPanelVisible->move(320, 140);
    controlPanelVisible->setChecked(true);
    QCheckBox *dateInfoVisible = new QCheckBox(this);
    dateInfoVisible->setText("date info visible");
    dateInfoVisible->setChecked(true);
    dateInfoVisible->move(320, 170);

    connect(cellSelectable, &QCheckBox::stateChanged, [calendar] (int state) -> void {calendar->setCellSelectable(state);});
    connect(festivalHighlight, &QCheckBox::stateChanged, [calendar] (int state) -> void {calendar->setLunarFestivalHighlight(state);});
    connect(lunarVisible, &QCheckBox::stateChanged, [calendar] (int state) -> void {calendar->setLunarVisible(state);});
    connect(controlPanelVisible, &QCheckBox::stateChanged, [calendar] (int state) -> void {calendar->setControlPanelVisible(state);});
    connect(dateInfoVisible, &QCheckBox::stateChanged, [calendar] (int state) -> void {calendar->setDateInfoVisible(state);});


    ////////////////////ArrowRectangle//////////////////
    DArrowRectangle *rectangle = new DArrowRectangle(DArrowRectangle::ArrowLeft);
//    rectangle->setArrowY(15);
    rectangle->setArrowX(25);
    rectangle->setArrowWidth(30);
    rectangle->setArrowHeight(10);
    QPushButton *button = new QPushButton("DArrowRectangle Test");
    button->setFixedSize(200, 30);
    rectangle->setContent(button);
    rectangle->show(200, 200);
}

