#ifndef IntelliPhotoGui_H
#define IntelliPhotoGui_H

#include <QList>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>

// PaintingArea used to paint the image
class PaintingArea;

class IntelliTool;

class IntelliColorPicker;

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
    void slotOpen();
    void slotSave();
    void slotCreateNewLayer();
    void slotDeleteLayer();

    void slotGetColorbar();
    void slotSwitchColors();
    void slotCreatePenTool();
    void slotCreateFloodFillTool();

    void slotAboutDialog();

    void slotClearActiveLayer();
    void slotSetActiveLayer();
    void slotSetActiveAlpha();
    void slotPositionMoveUp();
    void slotPositionMoveDown();
    void slotPositionMoveLeft();
    void slotPositionMoveRight();
    void slotMoveLayerUp();
    void slotMoveLayerDown();

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
    PaintingArea* paintingArea;

    // The menu widgets
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *layerMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;

    // All the actions that can occur
    QAction *actionOpen;
    QAction *actionExit;

    QAction *actionCreateNewLayer;
    QAction *actionDeleteLayer;

    QAction *actionGetColorbar;
    QAction *actionSwitchColors;
    QAction *actionCreatePenTool;
    QAction *actionCreateFloodFillTool;

    QAction *actionAboutDialog;
    QAction *actionAboutQtDialog;

    QAction* actionFloodFill;
    QAction* actionSetActiveLayer;
    QAction* actionSetActiveAlpha;
    QAction* actionMovePositionUp;
    QAction* actionMovePositionDown;
    QAction* actionMovePositionLeft;
    QAction* actionMovePositionRight;
    QAction* actionMoveLayerUp;
    QAction* actionMoveLayerDown;

    // Actions tied to specific file formats
    QList<QAction *> actionSaveAs;

    //main GUI elements
    QWidget* centralGuiWidget;
    QGridLayout *mainLayout;

};

#endif
