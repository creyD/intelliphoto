#ifndef INTELLIINPUTDIALOG_H
#define INTELLIINPUTDIALOG_H

#include <QtWidgets>
#include <QDebug>

class IntelliInputDialog : public QDialog
{
Q_OBJECT
public:
IntelliInputDialog(QEventLoop* Loop = nullptr, IntelliInputDialog* Dialog = nullptr, QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);

void getIntInput(QEventLoop* Loop = nullptr, IntelliInputDialog* Dialog = nullptr, QString Title = "InputBox", QString Label = "Weight:", int value = 0, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);

public slots:
void slotCloseEvent();
void slotEingabe();

private:
void createInputBox(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);
void createConnections(QEventLoop* Loop = nullptr);
void setValuesOfPalette();
void setInputBoxStyle();

QDialog* Dialog;

QGridLayout* Layout;
QDialogButtonBox* ButtonBox;

const QSize Linesize = QSize(150,20);
const QSize Buttonsize = QSize(72,20);
QPalette Palette;
QLabel* InputLabel;
QSpinBox* Input;
QPushButton* okButton;
QPushButton* cancelButton;
};

#endif // INTELLIINPUTDIALOG_H
