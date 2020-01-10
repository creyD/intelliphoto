#ifndef IntelliPhotoGui_H
#define IntelliPhotoGui_H

#include <QtWidgets>
#include <QPixmap>
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

/*!
 * \brief The IntelliPhotoGui class handles the graphical user interface for the intelliPhoto program
 */
class IntelliPhotoGui : public QMainWindow {
// Declares our class as a QObject which is the base class
// for all Qt objects
// QObjects handle events
Q_OBJECT
public:
/*!
 * \brief The IntelliPhotoGui method is the constructor and is used to create a new instance of the main program window
 */
IntelliPhotoGui();

void UpdateGui();

void setToolWidth(int value);

protected:
// Function used to close an event
void closeEvent(QCloseEvent*event) override;

private slots:
// meta slots here (need further )
void slotOpen();
void slotSave();

// layer slots here
void slotCreateNewLayer();
void slotDeleteLayer();
void slotClearActiveLayer();
void slotSetActiveLayer();
void slotSetActiveAlpha();
void slotPositionMoveUp();
void slotPositionMoveDown();
void slotPositionMoveLeft();
void slotPositionMoveRight();
void slotMoveLayerUp();
void slotMoveLayerDown();

//Rendersetting slots here
void slotUpdateRenderSettingsOn();
void slotUpdateRenderSettingsOff();

// color Picker slots here
void slotSetFirstColor();
void slotSetSecondColor();
void slotSwapColor();

// tool slots here
void slotCreatePenTool();
void slotCreatePlainTool();
void slotCreateLineTool();
void slotCreateRectangleTool();
void slotCreateCircleTool();
void slotCreatePolygonTool();
void slotCreateFloodFillTool();

// slots for dialogs
void slotAboutDialog();

void slotEnterPressed();

void slotSetWidth();
void slotSetInnerAlpha();

void slotResetTools();

private:
// Will tie user actions to functions
void createActions();
void createMenus();
// setup GUI elements
void createGui();
// set style of the GUI
void setIntelliStyle();

// Will check if changes have occurred since last save
bool maybeSave();
// Opens the Save dialog and saves
bool saveFile(const QByteArray &fileFormat);

void setDefaultToolValue();

// What we'll draw on
PaintingArea* paintingArea;

const QSize Buttonsize = QSize(35,35);
QPixmap preview;
QPushButton* CircleButton;
QPushButton* FloodFillButton;
QPushButton* LineButton;
QPushButton* PenButton;
QPushButton* PlainButton;
QPushButton* PolygonButton;
QPushButton* RectangleButton;
QLabel* WidthLine;
QLabel* innerAlphaLine;
QLineEdit* EditLineWidth;
QLineEdit* EditLineInnerAlpha;
QIntValidator* ValidatorLineWidth;
QIntValidator* ValidatorInnerAlpha;

QPushButton* FirstColorButton;
QPushButton* SecondColorButton;
QPushButton* SwitchColorButton;

QLabel* ActiveLayerLine;
QLabel* ActiveLayerImageLabel;

QPalette Palette;

// The menu widgets
QMenu*saveAsMenu;
QMenu*fileMenu;
QMenu*renderMenu;
QMenu*optionMenu;
QMenu*layerMenu;
QMenu*colorMenu;
QMenu*toolCreationMenu;
QMenu*toolSettingsMenu;
QMenu*toolMenu;
QMenu*helpMenu;

// All the actions that can occur
// meta image actions (need further modularisation)
QAction*actionOpen;
QAction*actionExit;

//Rendersetting actions
QAction*actionUpdateRenderSettingsOn;
QAction*actionUpdateRenderSettingsOff;

// color Picker actions
QAction*actionColorPickerFirstColor;
QAction*actionColorPickerSecondColor;
QAction*actionColorSwap;

// tool actions
QAction*actionCreatePenTool;
QAction*actionCreatePlainTool;
QAction*actionCreateLineTool;
QAction*actionCreateRectangleTool;
QAction*actionCreateCircleTool;
QAction*actionCreatePolygonTool;
QAction*actionCreateFloodFillTool;

// dialog actions
QAction*actionAboutDialog;
QAction*actionAboutQtDialog;

// layer change actions
QAction*actionCreateNewLayer;
QAction*actionDeleteLayer;
QAction* actionSetActiveLayer;
QAction* actionSetActiveAlpha;
QAction* actionMovePositionUp;
QAction* actionMovePositionDown;
QAction* actionMovePositionLeft;
QAction* actionMovePositionRight;
QAction* actionMoveLayerUp;
QAction* actionMoveLayerDown;

// Actions tied to specific file formats
QList<QAction*> actionSaveAs;

QAction* actionSetWidth;
QAction* actionSetInnerAlpha;

// main GUI elements
QWidget* centralGuiWidget;
QGridLayout* mainLayout;
};

#endif
