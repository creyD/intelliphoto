#ifndef IntelliPhotoGui_H
#define IntelliPhotoGui_H

#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>
#include <QMenu>
#include <QMenuBar>
#include <QList>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include "IntelliInputDialog.h"
#include "IntelliHelper/IntelliDatamanager.h"

//for unit testing
class UnitTest;

// PaintingArea used to paint the image
class PaintingArea;

class IntelliTool;

class IntelliColorPicker;

/*!
 * \brief The IntelliPhotoGui base class handles the graphical user interface and events for the intelliPhoto program
 */
class IntelliPhotoGui : public QMainWindow {
friend UnitTest;
// Declares our class as a QObject which is the base class
// for all Qt objects
// QObjects handle events
Q_OBJECT
public:
/*!
 * \brief The IntelliPhotoGui method is the constructor and is used to create a new instance of the main program window
 */
IntelliPhotoGui();

/*!
 * \brief UpdateGui a function to update all gui elements.
 */
void UpdateGui();

/*!
 * \brief setToolWidth stes a width to the tool
 * \param value - the width of the tool
 */
void setToolWidth(int value);

protected:
/*!
 * \brief The closeEvent function handles closing events
 */
void closeEvent(QCloseEvent*event) override;

private slots:

/*!
 * \brief slotOpen opens a new image
 */
void slotOpen();

/*!
 * \brief slotSave saves the current canvas
 */
void slotSave();

/*!
 * \brief slotCreateNewRasterLayer creates a new rasterImage
 */
void slotCreateNewRasterLayer();

/*!
 * \brief slotCreateNewShapedLayer creates a new shapedImage
 */
void slotCreateNewShapedLayer();

/*!
 * \brief slotDeleteLayer deletes a layer
 */
void slotDeleteLayer();

/*!
 * \brief slotSetActiveLayer sets a layer to be active
 */
void slotSetActiveLayer();

/*!
 * \brief slotSetActiveAlpha stes the alpha value of the active layer
 */
void slotSetActiveAlpha();

/*!
 * \brief slotSetPolygon sets a polygon to the active layer
 */
void slotSetPolygon();

/*!
 * \brief slotPositionMoveUp moves the current layer to the front
 */
void slotPositionMoveUp();

/*!
 * \brief slotPositionMoveDown moves the crrent layer to the back
 */
void slotPositionMoveDown();

/*!
 * \brief slotPositionMoveLeft moves the current layer left
 */
void slotPositionMoveLeft();

/*!
 * \brief slotPositionMoveRight moves the current layer right
 */
void slotPositionMoveRight();

/*!
 * \brief slotMoveLayerUp moves the current layer up
 */
void slotMoveLayerUp();

/*!
 * \brief slotMoveLayerDown moves the current layer down
 */
void slotMoveLayerDown();

/*!
 * \brief slotUpdateFastRenderSettingsOn activates the fast renderer
 */
void slotUpdateFastRenderSettingsOn();

/*!
 * \brief slotUpdateFastRenderSettingsOff deactivates the fast render
 */
void slotUpdateFastRenderSettingsOff();

/*!
 * \brief slotSetFirstColor sets the first color
 */
void slotSetFirstColor();

/*!
 * \brief slotSetSecondColor sets the second color
 */
void slotSetSecondColor();

/*!
 * \brief slotSwapColor swaps first and second color
 */
void slotSwapColor();

/*!
 * \brief slotCreatePenTool creates the pen tool
 */
void slotCreatePenTool();

/*!
 * \brief slotCreatePlainTool creates the plain tool
 */
void slotCreatePlainTool();

/*!
 * \brief slotCreateLineTool creates the line tool
 */
void slotCreateLineTool();

/*!
 * \brief slotCreateRectangleTool creates the rectangle tool
 */
void slotCreateRectangleTool();

/*!
 * \brief slotCreateCircleTool creates the cricle tool
 */
void slotCreateCircleTool();

/*!
 * \brief slotCreatePolygonTool creates the polygon tool
 */
void slotCreatePolygonTool();

/*!
 * \brief slotCreateFloodFillTool creates the floodfill tool
 */
void slotCreateFloodFillTool();

/*!
 * \brief slotCreateGradientTool creates the gradient tool
 */
void slotCreateGradientTool();

/*!
 * \brief slotAboutDialog displays the about dialog
 */
void slotAboutDialog();

/*!
 * \brief slotChangeDim changes the dimension of the canvas
 */
void slotChangeDim();

/*!
 * \brief slotEnterPressed read current input of input boxes, and adjusts settings
 */
void slotEnterPressed();

/*!
 * \brief slotSetWidth sets the width of the tool
 */
void slotSetWidth();

/*!
 * \brief slotSetInnerAlpha sets the inner alpha of the tool
 */
void slotSetInnerAlpha();

/*!
 * \brief slotResetTools resets all tool Buttons to unclikced
 */
void slotResetToolButtons();

/*!
 * \brief slotGoBack undoes the last action
 */
void slotGoBack();

/*!
 * \brief slotGoForward redoes  the last action
 */
void slotGoForward();

private:

/*!
 * \brief createActions creates all actions
 */
void createActions();

/*!
 * \brief createMenus creates all menus
 */
void createMenus();

/*!
 * \brief createGui sets up the gui
 */
void createGui();

/*!
 * \brief setIntelliStyle sets the stylesheet of the gui
 */
void setIntelliStyle();

/*!
 * \brief maybeSave chekcs if the canvas has unsaved work
 * \return return true if there is unsaved work, false otherwise
 */
bool maybeSave();

/*!
 * \brief saveFile saves the canvas
 * \param fileFormat the ileformat to save into
 * \return true if saving worked, false otherwise
 */
bool saveFile(const QByteArray &fileFormat);

/*!
 * \brief setDefaultValues sets basic tool values
 */
void setDefaultValues();

/*!
 * \brief paintingArea the logic manager of the backbone
 */
PaintingArea* paintingArea;

/*!
 * \brief preview a small pixmap to show the active layer
 */
QPixmap preview;

/*!
 * \brief Buttonsize the size of all standard buttons
 */
const QSize Buttonsize = QSize(35,35);

/*!
 * \brief CircleButton for creating a circle Tool
 */
QPushButton* CircleButton;

/*!
 * \brief FloodFillButton for creating a floodfill Tool
 */
QPushButton* FloodFillButton;

/*!
 * \brief GradientButton for creating a gradient Tool
 */
QPushButton* GradientButton;

/*!
 * \brief LineButton for creating a line Tool.
 */
QPushButton* LineButton;

/*!
 * \brief PenButton for creating a pen tool.
 */
QPushButton* PenButton;

/*!
 * \brief PlainButton for creating a plain Tool.
 */
QPushButton* PlainButton;

/*!
 * \brief PolygonButton for creating a Polygon Tool.
 */
QPushButton* PolygonButton;

/*!
 * \brief RectangleButton for creating a Rectangle Tool.
 */
QPushButton* RectangleButton;

/*!
 * \brief FirstColorButton for setting the First color.
 */
QPushButton* FirstColorButton;

/*!
 * \brief SecondColorButton for setting the Second color.
 */
QPushButton* SecondColorButton;

/*!
 * \brief SwitchColorButton for switching second and first color
 */
QPushButton* SwitchColorButton;

/*!
 * \brief dimActive for displaying the dimesnion of the active layer
 */
QPushButton* dimActive;

/*!
 * \brief dimCanvas for displaying the dimension of the canvas
 */
QPushButton* dimCanvas;

/*!
 * \brief WidthLine to indicate the line width
 */
QLabel* WidthLine;

/*!
 * \brief innerAlphaLine to indicate the inner alpha
 */
QLabel* innerAlphaLine;

/*!
 * \brief ActiveLayerLine to indicate the active Layer
 */
QLabel* ActiveLayerLabel;

/*!
 * \brief ActiveLayerImageLabel to indicate the active Image
 */
QLabel* ActiveLayerImageLabel;

/*!
 * \brief FastRendererLabel to indicate render settings
 */
QLabel* FastRendererLabel;

/*!
 * \brief ScrollArea to scroll the painting area on
 */
QScrollArea* ScrollArea;

/*!
 * \brief EditLineWidth to get the input of the line width
 */
QLineEdit* EditLineWidth;

/*!
 * \brief EditLineInnerAlpha to get the input of the inner alpha
 */
QLineEdit* EditLineInnerAlpha;

/*!
 * \brief ValidatorLineWidth to limit input
 */
QIntValidator* ValidatorLineWidth;

/*!
 * \brief ValidatorInnerAlpha to limit input
 */
QIntValidator* ValidatorInnerAlpha;


/*!
 * \brief saveAsMenu to display save options
 */
QMenu* saveAsMenu;

/*!
 * \brief fileMenu to display file options
 */
QMenu* fileMenu;

/*!
 * \brief renderMenu to display render options
 */
QMenu* renderMenu;

/*!
 * \brief optionMenu to display general options
 */
QMenu* optionMenu;

/*!
 * \brief layerCreationMenu to display layer creation options
 */
QMenu* layerCreationMenu;

/*!
 * \brief layerMenu to display layer options
 */
QMenu* layerMenu;

/*!
 * \brief colorMenu to display color options
 */
QMenu* colorMenu;

/*!
 * \brief toolCreationMenu to display tool creation options
 */
QMenu* toolCreationMenu;

/*!
 * \brief toolSettingsMenu to display settings options
 */
QMenu* toolSettingsMenu;

/*!
 * \brief toolMenu to display tool options
 */
QMenu* toolMenu;

/*!
 * \brief helpMenu to display the help options
 */
QMenu* helpMenu;

/*!
 * \brief actionOpen to open a project
 */
QAction* actionOpen;

/*!
 * \brief actionExit to exit the project
 */
QAction* actionExit;

/*!
 * \brief actionUpdateFastRenderSettingsOn to set fast render settings to on
 */
QAction* actionUpdateFastRenderSettingsOn;

/*!
 * \brief actionUpdateFastRenderSettingsOff to set fast render settings to false;
 */
QAction* actionUpdateFastRenderSettingsOff;

/*!
 * \brief actionColorPickerFirstColor to set the first color
 */
QAction* actionColorPickerFirstColor;

/*!
 * \brief actionColorPickerSecondColor to set the second color
 */
QAction* actionColorPickerSecondColor;

/*!
 * \brief actionColorSwap to swap first and second color
 */
QAction* actionColorSwap;

/*!
 * \brief actionCreatePenTool to create a pen tool
 */
QAction* actionCreatePenTool;

/*!
 * \brief actionCreatePlainTool to create a plain tool
 */
QAction* actionCreatePlainTool;

/*!
 * \brief actionCreateLineTool to create a line tool
 */
QAction* actionCreateLineTool;

/*!
 * \brief actionCreateRectangleTool to create a rectangle tool
 */
QAction* actionCreateRectangleTool;

/*!
 * \brief actionCreateCircleTool to create a circle tool
 */
QAction* actionCreateCircleTool;

/*!
 * \brief actionCreatePolygonTool to create a polygon tool
 */
QAction* actionCreatePolygonTool;

/*!
 * \brief actionCreateFloodFillTool to create a floodfill tool
 */
QAction* actionCreateFloodFillTool;

/*!
 * \brief actionCreateGradientTool to create a gradient tool
 */
QAction* actionCreateGradientTool;

/*!
 * \brief actionChangeDim
 */
QAction* actionChangeDim;

/*!
 * \brief actionSetWidth to set the width
 */
QAction* actionSetWidth;

/*!
 * \brief actionSetInnerAlpha to set the inner alha
 */
QAction* actionSetInnerAlpha;

/*!
 * \brief actionAboutDialog to show the
 */
QAction* actionAboutDialog;

/*!
 * \brief actionAboutQtDialog to show the qt input dialog
 */
QAction* actionAboutQtDialog;

/*!
 * \brief actionCreateNewRasterLayer creates a raster image
 */
QAction* actionCreateNewRasterLayer;

/*!
 * \brief actionCreateNewShapedLayer creates a shaped image
 */
QAction* actionCreateNewShapedLayer;

/*!
 * \brief actionDeleteLayer deletes a layer
 */
QAction* actionDeleteLayer;

/*!
 * \brief actionSetActiveLayer sets a layer to active
 */
QAction* actionSetActiveLayer;

/*!
 * \brief actionSetActiveAlpha sets the alpha of the active layer
 */
QAction* actionSetActiveAlpha;

/*!
 * \brief actionSetPolygon sets the polygon data to the image
 */
QAction* actionSetPolygon;

/*!
 * \brief actionMovePositionUp moves the image up
 */
QAction* actionMovePositionUp;

/*!
 * \brief actionMovePositionDown  moves the image down
 */
QAction* actionMovePositionDown;

/*!
 * \brief actionMovePositionLeft moves the image left
 */
QAction* actionMovePositionLeft;

/*!
 * \brief actionMovePositionRight moves the image right
 */
QAction* actionMovePositionRight;

/*!
 * \brief actionMoveLayerUp moves the layer to the front
 */
QAction* actionMoveLayerUp;

/*!
 * \brief actionMoveLayerDown moves the layer to the back
 */
QAction* actionMoveLayerDown;

/*!
 * \brief actionSaveAs saves the project as
 */
QList<QAction*> actionSaveAs;

/*!
 * \brief actionGoBack does a undo action
 */
QAction* actionGoBack;

/*!
 * \brief actionGoForward does a redo action
 */
QAction* actionGoForward;

/*!
 * \brief centralGuiWidget the main gui widget to place all others on
 */
QWidget* centralGuiWidget;

/*!
 * \brief mainLayout the layout to order all gui elements
 */
QGridLayout* mainLayout;
};

#endif
