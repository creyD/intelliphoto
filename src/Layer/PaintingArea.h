
#ifndef PaintingArea_H
#define PaintingArea_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QList>
#include "GUI/IntelliPhotoGui.h"
#include "Image/IntelliImage.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"
#include "Tool/IntelliTool.h"
#include "IntelliHelper/IntelliColorPicker.h"

/*!
 * \brief The LayerObject struct holds all the information needed to construct a layer
 * \param width         - Stores the width of a layer in pixels
 * \param height        - Stores the height of a layer in pixels
 * \param alpha         - Stores the alpha value of the layer (default=255)
 * \param widthOffset   - Stores the number of pixles from the left side of the painting area
 * \param heightOffset  - Stores the number of pixles from the top of the painting area
 */
struct LayerObject {
		IntelliImage* image;
		int width;
		int height;
		int widthOffset;
		int heightOffset;
		int alpha=255;
};

/*!
 * \brief The PaintingArea class manages the methods and stores information about the current painting area, which is the currently opened project
 */
class PaintingArea : public QWidget
{
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
PaintingArea(int maxWidth=600, int maxHeight=600, QWidget*parent = nullptr);

/*!
 * \brief This deconstructor is used to clear up the memory and remove the currently active window
 */
~PaintingArea() override;

// Handles all events

/*!
 * \brief setRenderSettings updates all Images to the new Rendersetting.
 * \param isFastRenderingOn is the new given flag for the FastRenderer.
 */
void setRenderSettings(bool isFastRenderingOn);

/*!
 * \brief The open method is used for loading a picture into the current layer
 * \param fileName  - Path and filename which are used to determine where the to-be-opened file is stored
 * \return Returns a boolean variable whether the file was successfully opened or not
 */
bool open(const QString &filePath);
/*!
 * \brief The save method is used for exporting the current project as one picture
 * \param fileName
 * \param fileFormat
 * \return Returns a boolean variable, true if the file was saved successfully, false if not
 */
bool save(const QString &filePath, const char*fileFormat);

/*!
 * \brief The addLayer adds a layer to the current project/ painting area
 * \param width         - Width of the layer in pixles
 * \param height        - Height of the layer in pixles
 * \param widthOffset   - Offset of the layer measured to the left border of the painting area in pixles
 * \param heightOffset  - Offset of the layer measured to the top border of the painting area in pixles
 * \param type          - Defining the ImageType of the new layer
 * \return  Returns the number of layers in the project
 */
int addLayer(int width, int height, int widthOffset=0, int heightOffset=0, IntelliImage::ImageType type = IntelliImage::ImageType::RASTERIMAGE);
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
int addLayerAt(int idx, int width, int height, int widthOffset=0, int heightOffset=0, IntelliImage::ImageType type = IntelliImage::ImageType::RASTERIMAGE);
/*!
 * \brief The deleteLayer method removes a layer at a given idx
 * \param idx - The index of the layer to be removed
 */
void deleteLayer(int idx);
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
 * \brief The floodFill method fills a the active layer with a given color
 * \param r     - Red value of the color the layer should be filled with
 * \param g     - Green value of the color the layer should be filled with
 * \param b     - Blue value of the color the layer should be filled with
 * \param a     - Alpha value of the color the layer should be filled with
 */
void floodFill(int r, int g, int b, int a);
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

//change properties of colorPicker
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

// Create tools
void createPenTool();
void createPlainTool();
void createLineTool();
void createRectangleTool();
void createCircleTool();
void createPolygonTool();
void createFloodFillTool();

/*!
 * \brief The getWidthOfActive gets the horizontal dimensions of the active layer
 * \return Returns the horizontal pixle count of the active layer
 */
int getWidthOfActive();
/*!
 * \brief The getHeightOfActive gets the vertical dimensions of the active layer
 * \return Returns the vertical pixle count of the active layer
 */
int getHeightOfActive();

IntelliImage::ImageType getTypeOfImageRealLayer();

std::vector<QPoint> getPolygonDataOfRealLayer();

int getNumberOfActiveLayer();

IntelliImage* getImageOfActiveLayer();

/*!
 * \brief getImageDataOfActiveLayer used to get the currents active imageData (if there isn't any active layer it return a 10*10 white picture)
 * \return return the image as an rgba32bit qImage
 */
QImage getImageDataOfActiveLayer();

IntelliToolsettings Toolsettings;
IntelliColorPicker colorPicker;

public slots:
// Events to handle
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
void mousePressEvent(QMouseEvent*event) override;
void mouseMoveEvent(QMouseEvent*event) override;
void mouseReleaseEvent(QMouseEvent*event) override;

void wheelEvent(QWheelEvent*event) override;
// Updates the painting area where we are painting
void paintEvent(QPaintEvent*event) override;

// Makes sure the area we are drawing on remains
// as large as the widget
void resizeEvent(QResizeEvent*event) override;

private:
void setLayerDimensions(int maxWidth, int maxHeight);
void selectLayerUp();
void selectLayerDown();
IntelliTool* copyActiveTool();

QImage* Canvas;
int maxWidth;
int maxHeight;

IntelliRenderSettings renderSettings;
IntelliTool* Tool;
IntelliPhotoGui* DummyGui;

std::vector<LayerObject> layerBundle;
int activeLayer=-1;

void drawLayers(bool forSaving=false);

void resizeLayer(QImage*image_res, const QSize &newSize);

// Helper for Tool
bool createTempTopLayer(int idx);
};

#endif
