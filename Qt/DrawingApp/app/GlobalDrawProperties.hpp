#pragma once

#include <QColor>
#include <QObject>

#include "ChangePropertyCommandList.hpp"
class VisualEntity;
class PropertyColorButton;
class PropertySpinBox;
class PropertyNameLineEdit;
class Selection;

// singleton
class GlobalDrawProperties : public QObject
{
	Q_OBJECT

public:
    static GlobalDrawProperties& getInstance();
    void setup(PropertyColorButton *fillColorProp,
               PropertyColorButton *lineColorProp,
               //PropertySpinBox *thicknessProp,
               PropertyNameLineEdit *nameLineProp);
    void setVEProperties(VisualEntity *ve);
    QColor getFillColor();
    QColor getLineColor();
    bool isSetup() { return m_isSetup; }
    //int getThickness();
    QString getNameLine();
    void update(size_t selSize);
    void unlinkProperties();

private slots:
    void onClickFillColor();
    void onSelectFillColor(QColor color);
    void onRejectFillColor();

    void onClickLineColor();
    void onSelectLineColor(QColor color);
    void onRejectLineColor();

private:
    PropertyColorButton *m_fillColorProp;
    PropertyColorButton *m_lineColorProp;
    //PropertySpinBox *m_thicknessProp;
    PropertyNameLineEdit *m_nameLineProp;

    bool m_isSetup;
    ActiveSelection *m_as;

    ChangeFillColorCommand *m_changeFillColorComm;
    ChangeLineColorCommand *m_changeLineColorComm;

    GlobalDrawProperties();
    ~GlobalDrawProperties() {}
};

