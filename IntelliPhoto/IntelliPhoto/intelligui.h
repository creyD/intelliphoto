#ifndef INTELLIGUI_H
#define INTELLIGUI_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class IntelliGUI; }
QT_END_NAMESPACE

class IntelliGUI : public QMainWindow
{
    Q_OBJECT
    QWidget *GUI;

private:
    Ui::IntelliGUI *ui;
    QString color="rgb(255,255,255)";

public:
    IntelliGUI(QWidget *parent = nullptr);
    ~IntelliGUI();

    //COlor Values between 0 and 1
    void setColor(double R, double G, double B);
    void setColor(int R, int G, int B);

private slots:
};
#endif // INTELLIGUI_H
