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

class PaintingArea;

class IntelliTool;

class IntelliColorPicker;

/*!
 * \brief The IntelliPhotoGui base class handles the graphical user interface and events for the intelliPhoto program
 */
class IntelliPhotoGui : public QMainWindow {
Q_OBJECT
public:
/*!
 * \brief The IntelliPhotoGui method is the constructor and is used to create a new instance of the main program window
 */
IntelliPhotoGui();

void UpdateGui();

protected:
/*!
 * \brief The closeEvent function handles closing events
 */
void closeEvent(QCloseEvent*event) override;

private slots:
void slotOpen();
void slotSave();

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

void slotUpdateRenderSettingsOn();
void slotUpdateRenderSettingsOff();

void slotSetFirstColor();
void slotSetSecondColor();
void slotSwapColor();

void slotCreatePenTool();
void slotCreatePlainTool();
void slotCreateLineTool();
void slotCreateRectangleTool();
void slotCreateCircleTool();
void slotCreatePolygonTool();
void slotCreateFloodFillTool();

void slotAboutDialog();

void slotEnterPressed();

void slotSetWidth();
void slotSetInnerAlpha();

void slotResetTools();

private:
void createActions();
void createMenus();
void createGui();
// Set the style of the GUI
void setIntelliStyle();

// Will check if changes have occurred since last save
bool maybeSave();
// Opens the Save dialog and saves
bool saveFile(const QByteArray &fileFormat);

void setDefaultToolValue();

// What we'll draw on
PaintingArea* paintingArea;

const QSize Buttonsize = QSize(70,70);
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
QLabel* ActiveLayerImageLine;

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
