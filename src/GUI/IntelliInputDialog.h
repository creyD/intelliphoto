#ifndef INTELLIINPUTDIALOG_H
#define INTELLIINPUTDIALOG_H

#include <QtWidgets>

class IntelliInputDialog : public QDialog
{
Q_OBJECT
public:
IntelliInputDialog(QEventLoop* Loop = nullptr, QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);


static int getInt(QEventLoop* Loop = nullptr, QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);

public slots:
void slotCloseEvent();
void slotEingabe();

private:
void createInputBox(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);
void createConnections(QEventLoop* Loop = nullptr);
void setValuesOfPalette();
void setInputBoxStyle();

int valueInt;

QGridLayout* Layout;
QDialogButtonBox* ButtonBox;
QEventLoop loop;

const QSize Linesize = QSize(150,20);
const QSize Buttonsize = QSize(72,20);
QPalette Palette;
QLabel* InputLabel;
QSpinBox* Input;
QPushButton* okButton;
QPushButton* cancelButton;
};

#endif // INTELLIINPUTDIALOG_H
