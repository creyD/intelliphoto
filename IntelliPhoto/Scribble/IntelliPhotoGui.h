#ifndef IntelliPhotoGui_H
#define IntelliPhotoGui_H

#include <QList>
#include <QMainWindow>
#include<QGridLayout>
#include<QPushButton>

// ScribbleArea used to paint the image
class PaintingArea;

class IntelliPhotoGui : public QMainWindow
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT

public:
    IntelliPhotoGui();
protected:
    // Function used to close an event
    void closeEvent(QCloseEvent *event) override;

// The events that can be triggered
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    // Will tie user actions to functions
    void createActions();
    void createMenus();

    //setup GUI elements
    void createGui();

    //set style of the GUI
    void setIntelliStyle();

    // Will check if changes have occurred since last save
    bool maybeSave();

    // Opens the Save dialog and saves
    bool saveFile(const QByteArray &fileFormat);

    // What we'll draw on
    PaintingArea *paintingArea;

    // The menu widgets
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    // All the actions that can occur
    QAction *openAct;

    // Actions tied to specific file formats
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    //main GUI elements
    QWidget* centralGuiWidget;
    QGridLayout *mainLayout;
    QPushButton *clearButton;
};

#endif
