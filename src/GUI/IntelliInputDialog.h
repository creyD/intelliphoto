#ifndef INTELLIINPUTDIALOG_H
#define INTELLIINPUTDIALOG_H

#include <QtWidgets>

class IntelliInputDialog : public QDialog
{
Q_OBJECT
public:
IntelliInputDialog(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1, bool* ok = nullptr);


static int getInt(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1, bool* ok = nullptr);

public slots:
void slotCloseEvent();
void slotEingabe();

private:
void createInputBox(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);
void createConnections();
void setInputBoxStyle();

int valueInt;

QGridLayout* Layout;
QDialogButtonBox* ButtonBox;
QEventLoop loop;
bool* notClosed;

const QSize Linesize = QSize(150,20);
const QSize Buttonsize = QSize(72,20);
QLabel* InputLabel;
QSpinBox* Input;
QPushButton* okButton;
QPushButton* cancelButton;
};

#endif // INTELLIINPUTDIALOG_H
