
#ifndef PaintingArea_H
#define PaintingArea_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QList>
#include <QLabel>
#include "Image/IntelliImage.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"
#include "Tool/IntelliTool.h"
#include "IntelliHelper/IntelliColorPicker.h"

//for unit testing
class UnitTest;
class IntelliPhotoGui;
/*!
 * \brief The LayerObject struct holds all the information needed to construct a layer
 */
struct LayerObject {
		/*!
		 * \brief image -   Stores the imageData of the current LayerObject.
		 */
		IntelliImage* image;
		/*!
		 * \brief width - Stores the width of a layer in pixels.
		 */
		int width;
		/*!
		 * \brief height - Stores the height of a layer in pixels.
		 */
		int height;
		/*!
		 * \brief  widthOffset - Stores the number of pixles from the left side of the painting area.
		 */
		int widthOffset;
		/*!
		 * \brief heightOffset - Stores the number of pixles from the top of the painting area.
		 */
		int heightOffset;
		/*!
		 * \brief alpha - Stores the alpha value of the layer (default=255).
		 */
		int alpha = 255;

		LayerObject();

		LayerObject(const LayerObject& layer);
};

/*!
 * \brief The PaintingArea class manages the methods and stores information about the current painting area, which is the currently opened project
 */
class PaintingArea : public QLabel
{
friend UnitTest;
// Declares our class as a QObject which is the base class
// for all Qt objects
// QObjects handle events
Q_OBJECT
friend IntelliTool;
friend IntelliPhotoGui;
public:
/*!
 * \brief PaintingArea is the constructor of the PaintingArea class, which initiates the working environment
 * \param maxWidth      - The maximum amount of pixles that are inside painting area from left to right (default=600px)
 * \param maxHeight     - The maximum amount of pixles that are inside painting area from top to bottom (default=600px)
 * \param parent        - The parent window of the main window (default=nullptr)
 */
PaintingArea(int maxWidth = 600, int maxHeight = 600, QWidget*parent = nullptr);

/*!
 * \brief This deconstructor is used to clear up the memory and remove the currently active window
 */
~PaintingArea() override;

/*!
 * \brief setRenderSettings updates all Images to the new Rendersetting.
 * \param isFastRenderingOn is the new given flag for the FastRenderer.
 */
void setRenderSettings(bool isFastRenderingOn);

/*!
 * \brief getRenderSettings updates all Images to the new Rendersetting.
 * \param isFastRenderingOn is the new given flag for the FastRenderer.
 */
bool getRenderSettings();

/*!
 * \brief The open method is used for loading a picture into the current layer.
 * \param filePath  - Path and Name which are used to determine where the to-be-opened file is stored.
 * \return Returns a boolean variable whether the file was successfully opened or not.
 */
bool open(const QString &filePath);
/*!
 * \brief The save method is used for exporting the current project as one picture
 * \param filePath - Specifies the path and name of the file to create.
 * \param fileFormat - Specifies the format of the file to create.
 * \return Returns a boolean variable, true if the file was saved successfully, false if not
 */
bool save(const QString &filePath, const char*fileFormat);

/*!
 * \brief deleteAllLayers deletes all layers
 */
void deleteAllLayers();
/*!
 * \brief The addLayer adds a layer to the current project/ painting area
 * \param width         - Width of the layer in pixles
 * \param height        - Height of the layer in pixles
 * \param widthOffset   - Offset of the layer measured to the left border of the painting area in pixles
 * \param heightOffset  - Offset of the layer measured to the top border of the painting area in pixles
 * \param alpha         - Transparence of the layer
 * \param type          - Defining the ImageType of the new layer
 * \return  Returns the number of layers in the project
 */
int addLayer(int width, int height, int widthOffset = 0, int heightOffset = 0, int alpha = 255, ImageType type = ImageType::RASTERIMAGE);
/*!
 * \brief The addLayerAt adds a layer to the current project/ painting area at a specific position in the layer stack
 * \param idx           - Index of the position the new layer should be added
 * \param width         - Width of the layer in pixles
 * \param height        - Height of the layer in pixles
 * \param widthOffset   - Offset of the layer measured to the left border of the painting area in pixles
 * \param heightOffset  - Offset of the layer measured to the top border of the painting area in pixles
 * \param type          - Defining the ImageType of the new layer
 * \return  Returns the id of the layer position
 */
int addLayerAt(int idx, int width, int height, int widthOffset = 0, int heightOffset = 0, ImageType type = ImageType::RASTERIMAGE);
/*!
 * \brief The deleteLayer method removes a layer at a given idx
 * \param idx - The index of the layer to be removed
 * \param isTool - Is the flag for when a tool uses this function.
 */
void deleteLayer(int idx, bool isTool = false);
/*!
 * \brief The setLayerToActive method marks a specific layer as active
 * \param idx - The index of the layer to be active
 */
void setLayerActive(int idx);
/*!
 * \brief The setAlphaOfLayer method sets the alpha value of a specific layer
 * \param idx     - The index of the layer where the change should be applied
 * \param alpha     - New alpha value of the layer
 */
void setLayerAlpha(int idx, int alpha);
/*!
 * \brief setPolygon is used for setting polygondata, it only works on RASTER images
 * \param idx - represents the number of the layer with should be transformed
 */
void setPolygon(int idx);
/*!
 * \brief The movePositionActive method moves the active layer to certain position
 * \param x     - The x value the new center of the layer should be at
 * \param y     - The y value the new center of the layer should be at
 */
void movePositionActive(int x, int y);
/*!
 * \brief The moveActiveLayer moves the active layer to a specific position in the layer stack
 * \param idx   - The index of the new position the layer should be in
 */
void moveActiveLayer(int idx);

/*!
 * \brief The colorPickerSetFirstColor calls the QTColorPicker to determine the primary drawing color
 */
void colorPickerSetFirstColor();
/*!
 * \brief The colorPickerSetSecondColor calls the QTColorPicker to determine the secondary drawing color
 */
void colorPickerSetSecondColor();
/*!
 * \brief The colorPickerSwitchColor swaps the primary color with the secondary drawing color
 */
void colorPickerSwapColors();

/*!
 * \brief createPenTool creates a Pen Tool.
 */
void createPenTool();

/*!
 * \brief createPlainTool creates a Plain Tool.
 */
void createPlainTool();

/*!
 * \brief createLineTool creates a Line Tool.
 */
void createLineTool();

/*!
 * \brief createRectangleTool creates a Rectangle Tool.
 */
void createRectangleTool();

/*!
 * \brief createCircleTool creates a Circle Tool.
 */
void createCircleTool();

/*!
 * \brief createPolygonTool creates a Polygon Tool.
 */
void createPolygonTool();

/*!
 * \brief createFloodFillTool creates a Floodfill Tool.
 */
void createFloodFillTool();

/*!
 * \brief createGradientTool creates a Gradient Tool.
 */
void createGradientTool();

/*!
 * \brief The getWidthOfActive gets the horizontal dimensions of the active layer.
 * \return Returns the horizontal pixle count of the active layer.
 */
int getWidthOfActive();
/*!
 * \brief The getHeightOfActive gets the vertical dimensions of the active layer.
 * \return Returns the vertical pixle count of the active layer.
 */
int getHeightOfActive();

/*!
 * \brief getMaxWidth gets the max width of the Canvas.
 * \return return the width of the Canvas.
 */
int getMaxWidth();

/*!
 * \brief getMaxHeight gets the max height of the Canvas.
 * \return return the height of the Canvas.
 */
int getMaxHeight();

/*!
 * \brief getTypeOfImageActiveLayer get the type of the active Layer.
 * \return returns the image type of the active layer.
 */
ImageType getTypeOfImageActiveLayer();

/*!
 * \brief getPolygonDataOfActiveLayer get the polygon data of the active Layer.
 * \return return the polygon data of the active Layer.
 */
std::vector<QPoint> getPolygonDataOfActiveLayer();

/*!
 * \brief getIndexOfActiveLayer returns the index of athe active Layer.
 * \return return the index of the active Layer.
 */
int getIndexOfActiveLayer();

/*!
 * \brief getImageOfActiveLayer returns the image of the active Layer.
 * \return return the image of the active Layer.
 */
IntelliImage* getImageOfActiveLayer();

/*!
 * \brief getImageDataOfActiveLayer used to get the currents active imageData (if there isn't any active layer it return a 10*10 white picture)
 * \return return the image as an rgba32bit qImage
 */
QImage getImageDataOfActiveLayer();

/*!
 * \brief getLayerBundle returns the real active layerbundle (care!)
 * \return the reference of the currentLayerBundle
 */
std::vector<LayerObject>* getLayerBundle();

/*!
 * \brief Toolsettings - a class to manage Tool settings.
 */
IntelliToolsettings Toolsettings;

/*!
 * \brief colorPicker a class to manage Tool color.
 */
IntelliColorPicker colorPicker;

/*!
 * \brief historyadd adds an hisotry step
 */
void historyadd();

/*!
 * \brief historyGoBack go back in hisotry
 */
void historyGoBack();

/*!
 * \brief historyGoForward a function to undo the return of the previous state of the project.
 */
void historyGoForward();

/*!
 * \brief setCanvasDimensions sets the dimension of the Canvas
 * \param maxWidth  - the width of the Canvas.
 * \param maxHeight - the height of the Canvas.
 */
void setCanvasDimensions(int maxWidth, int maxHeight);

/*!
 * \brief drawPixelOntoActive draws a pixel onto the image data of the active Layer.
 * \param color - the color of the Pixel, which should be created.
 * \param point - the Pixelposition.
 */
void drawPixelOntoActive(QColor color, QPoint point);

/*!
 * \brief setPolygonDataToActive sets polygondata to the active Layer.
 * \param points - the points of the polygon data.
 */
void setPolygonDataToActive(std::vector<QPoint> points);
public slots:
/*!
 * \brief The slotActivateLayer method handles the event of selecting one layer as active
 * \param a - idx of the layer to be active
 */
void slotActivateLayer(int a);
/*!
 * \brief The slotDeleteActiveLayer method handles the deletion of the active layer
 */
void slotDeleteActiveLayer();

protected:
/*!
 * \brief mousePressEvent handles a mouse pressed event.
 * \param event - the specific mouse event.
 */
void mousePressEvent(QMouseEvent*event) override;

/*!
 * \brief mouseMoveEvent handles a mouse moved event
 * \param event - the specific mouse event.
 */
void mouseMoveEvent(QMouseEvent*event) override;

/*!
 * \brief mouseReleaseEvent handles a mouse released event
 * \param event - the specific mouse event.
 */
void mouseReleaseEvent(QMouseEvent*event) override;

/*!
 * \brief wheelEvent handles a mouse wheel event
 * \param event - the specific mouse event.
 */
void wheelEvent(QWheelEvent*event) override;

/*!
 * \brief paintEvent handles a painting event
 * \param event - the specific paint event.
 */
void paintEvent(QPaintEvent*event) override;

private:
/*!
 * \brief offsetXDimension - Offset for drawing the image.
 */
int offsetXDimension;

/*!
 * \brief offsetYDimension - Offset for drawing the image.
 */
int offsetYDimension;

/*!
 * \brief selectLayerUp moves the active Layer one Up.
 */
void selectLayerUp();

/*!
 * \brief selectLayerDown moves the active Layer one Down.
 */
void selectLayerDown();

/*!
 * \brief copyActiveTool copys the activ tool [allocated].
 * \return returns a allocates copy of the current tool.
 */
IntelliTool* copyActiveTool();

/*!
 * \brief Canvas the underlying Image to display on.
 */
QImage* Canvas;

/*!
 * \brief ScaledCanvas the Canvas saved for output
 */
QImage ScaledCanvas;

/*!
 * \brief maxWidth is the width of the canvas
 */
int maxWidth;

/*!
 * \brief maxHeight is the height of the canvas
 */
int maxHeight;

/*!
 * \brief isSettingPolygon for checking the state of the drawing.
 */
bool isSettingPolygon = false;

/*!
 * \brief renderSettings a class to manage the render settings.
 */
IntelliRenderSettings renderSettings;

/*!
 * \brief Tool a class to manage the Tool.
 */
IntelliTool* Tool;

/*!
 * \brief guiReference to manage communication with the gui.
 */
IntelliPhotoGui* guiReference;

/*!
 * \brief layerBundle a container to save all layers.
 */
std::vector<LayerObject> layerBundle;

/*!
 * \brief activeLayer the index of the active Layer.
 */
int activeLayer = -1;

/*!
 * \brief drawLayers draws the Layers to the Canvas
 * \param forSaving an indecate if drawing for saving.
 */
void drawLayers(bool forSaving = false);

/*!
 * \brief createTempTopLayer creates a temporary Layer on top of the Layer.
 * \param idx - the Layer which should get a temp Layer.
 * \return True if it workes, false otherwise.
 */
bool createTempTopLayer(int idx);

/*!
 * \brief updateTools resets the Tools.
 */
void updateTools();

/*!
 * \brief history - an array out of containers to save history actions.
 */
std::vector<LayerObject> history[100] = {layerBundle};

/*!
 * \brief historyMaxPast a indicator how many steps you can go into the past.
 */
int historyMaxPast = 0;

/*!
 * \brief historyMaxPast a indicator how many steps you can go into the future.
 */
int historyMaxFuture = 0;

/*!
 * \brief historyPresent a indicator where the present is.
 */
int historyPresent = 0;

};

#endif
