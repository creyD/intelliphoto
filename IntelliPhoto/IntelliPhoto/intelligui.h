#ifndef INTELLIGUI_H
#define INTELLIGUI_H

#include <QMainWindow>
#include <QPushButton>
#include <LayerManager.h>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class IntelliGUI; }
QT_END_NAMESPACE

class IntelliGUI : public QMainWindow
{
    Q_OBJECT
    //basics for programm logic
    LayerManager *EbenenManager;

    //basics for GUI build
    QWidget *GUI;
    QGridLayout *Layout;

    //Declare all Gui elements down here
    QPushButton *EinKnopf;

private:
    Ui::IntelliGUI *ui;

public:
    //Sets up everything to display first loaded projekt, maybe show load window for a project
    IntelliGUI(QWidget *parent = nullptr);
    //Delets everything in connection to one project
    ~IntelliGUI();

private slots:
};
#endif // INTELLIGUI_H
