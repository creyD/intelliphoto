#ifndef INTELLIINPUTDIALOG_H
#define INTELLIINPUTDIALOG_H

#include <QSize>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QSpinBox>

/*!
 * \brief The IntelliInputDialog class is a customized Input Dialog to get Integers
 */
class IntelliInputDialog : public QDialog
{
Q_OBJECT
public:
/*!
 * \brief IntelliInputDialog is the baisc constructor to for the InputDialog
 * \param Title     - Title of the Input Dialog.
 * \param Label     - A Label for the Iput Dialog, to show further information.
 * \param value     - The standart value in the Input Box.
 * \param minValue  - The minimal value to read.
 * \param maxValue  - The maximal value to read.
 * \param step      - The step size of Values.
 * \param ok        - A check if the input was okay
 */
IntelliInputDialog(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1, bool* ok = nullptr);

/*!
 * \brief getInt is a static funktion ´, which creates an Input Dialog and gets an Integer.
 * \param Title     - Title of the Input Dialog.
 * \param Label     - A Label for the Iput Dialog, to show further information.
 * \param value     - The standart value in the Input Box.
 * \param minValue  - The minimal value to read.
 * \param maxValue  - The maximal value to read.
 * \param step      - The step size of Values.
 * \param ok        - A check if the input was okay
 * \return
 */
static int getInt(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1, bool* ok = nullptr);

public slots:
/*!
 * \brief slotCloseEvent is a slot for catching the close Event.
 */
void slotCloseEvent();

/*!
 * \brief slotEingabe is a slot for catching the Input Event.
 */
void slotEingabe();

private:
/*!
 * \brief createInputBox creates an Input Box for reading values.
 * \param Title     - Title of the Input Dialog.
 * \param Label     - A Label for the Iput Dialog, to show further information.
 * \param value     - The standart value in the Input Box.
 * \param minValue  - The minimal value to read.
 * \param maxValue  - The maximal value to read.
 * \param step      - The step size of Values.
 */
void createInputBox(QString Title = nullptr, QString Label = nullptr, int value = 5, int minValue = -2147483647, int maxValue = 2147483647, int step = 1);

/*!
 * \brief createConnections connects the close and Eingabe slot.
 */
void createConnections();

/*!
 * \brief setInputBoxStyle
 */
void setInputBoxStyle();

/*!
 * \brief valueInt the variable where the input is saved.
 */
int valueInt;

/*!
 * \brief Layout to place als gui event onto.
 */
QGridLayout* Layout;

/*!
 * \brief ButtonBox is a gui elment for the button.
 */
QDialogButtonBox* ButtonBox;

/*!
 * \brief notClosed saves the value, if the InputDialog is closed.
 */
bool* notClosed;

/*!
 * \brief Linesize to standarize the line size.
 */
const QSize Linesize = QSize(150,20);

/*!
 * \brief Buttonsize to standarize the button size.
 */
const QSize Buttonsize = QSize(72,20);

/*!
 * \brief InputLabel a gui element for a label.
 */
QLabel* InputLabel;

/*!
 * \brief Input a gui element for a SpinBox.
 */
QSpinBox* Input;

/*!
 * \brief okButton a gui element for the ok Button.
 */
QPushButton* okButton;

/*!
 * \brief cancelButton a gui element for the cancel button.
 */
QPushButton* cancelButton;
};

#endif // INTELLIINPUTDIALOG_H
