#ifndef INTELLIIMAGE_H
#define INTELLIIMAGE_H

#include <QImage>
#include <QPoint>
#include <QColor>
#include <QSize>
#include <QWidget>
#include <vector>

#include "IntelliHelper/IntelliTriangulation.h"
#include "IntelliHelper/IntelliRenderSettings.h"

//for unit testing
class UnitTest;

class IntelliTool;

/*!
 * \brief An abstract class which manages the basic IntelliImage operations.
 */
class IntelliImage {
    friend UnitTest;
friend IntelliTool;
public:

/*!
 * \brief The Types, which an Image can be.
 */
enum class ImageType {
		RASTERIMAGE,
		SHAPEDIMAGE
};

protected:
void resizeImage(QImage*image, const QSize &newSize);

/*!
 * \brief The underlying image data.
 */
QImage imageData;

/*!
 * \brief The Type, an Image is.
 */
ImageType TypeOfImage;

/*!
 * \brief fastRendering is the flag that represents the usage of 8bit pictures.
 */
bool fastRenderering;

public:
/*!
 * \brief The Construcor of the IntelliImage. Given the Image dimensions.
 * \param width    - The width of the Image.
 * \param height    - The height of the Image.
 * \param fastRendererOn    - Represents the flag for 8bit picture handelling.
 */
IntelliImage(int width, int height, bool fastRendererOn);

/*!
 * \brief An Abstract Destructor.
 */
virtual ~IntelliImage() = 0;


/*!
 * \brief A funtcion used to draw a pixel on the Image with the given Color.
 * \param p1    - The coordinates of the pixel, which should be drawn. [Top-Left-System]
 * \param color - The color of the pixel.
 */
virtual void drawPixel(const QPoint &p1, const QColor& color);

/*!
 * \brief A function that draws A Line between two given Points in a given color.
 * \param p1        - The coordinates of the first Point.
 * \param p2        - The coordinates of the second Point.
 * \param color     - The color of the line.
 * \param penWidth  - The width of the line.
 */
virtual void drawLine(const QPoint &p1, const QPoint& p2, const QColor& color, const int& penWidth);

/*!
 * \brief A
 * \param p1
 * \param color
 * \param penWidth
 */
virtual void drawPoint(const QPoint &p1, const QColor& color, const int& penWidth);

/*!
 * \brief A function that clears the whole image in a given Color.
 * \param color - The color, in which the image will be filled.
 */
virtual void drawPlain(const QColor& color);

/*!
 * \brief A function returning the displayable ImageData in a requested transparence and size.
 * \param displaySize   - The size, in whcih the Image should be displayed.
 * \param alpha         - The maximum alpha value, a pixel can have.
 * \return A QImage which is ready to be displayed.
 */
virtual QImage getDisplayable(const QSize& displaySize, int alpha) = 0;

/**
 * @brief A function returning the displayable ImageData in a requested transparence and it's standart size.
 * @param alpha - The maximum alpha value, a pixel can have.
 * @return A QImage which is ready to be displayed.
 */
virtual QImage getDisplayable(int alpha = 255) = 0;

/*!
 * \brief A function that copys all that returns a [allocated] Image
 * \return An [allocated] image with all the properties of the instance.
 */
virtual IntelliImage* getDeepCopy() = 0;

/*!
 * \brief An abstract function that calculates the visiblity of the Image data if needed.
 */
virtual void calculateVisiblity() = 0;

/*!
 * \brief An abstract function that sets the data of the visible Polygon, if needed.
 * \param polygonData   - The Vertices of the Polygon. Just Planar Polygons are allowed.
 */
virtual void setPolygon(const std::vector<QPoint>& polygonData) = 0;

/*!
 * \brief A function that returns the Polygondata if existent.
 * \return The Polygondata if existent.
 */
virtual std::vector<QPoint> getPolygonData(){
		return std::vector<QPoint>();
}

virtual ImageType getTypeOfImage(){
		return TypeOfImage;
}

/*!
 * \brief A function that loads and sclaes an image to the fitting dimensions.
 * \param filePath  - The path+name of the image which to loaded.
 * \return True if the image could be loaded, false otherwise.
 */
virtual bool loadImage(const QString &filePath);

/*!
 * \brief A function that returns the pixelcolor at a certain point
 * \param point - The point from whcih to get the coordinates.
 * \return The color of the Pixel as QColor.
 */
virtual QColor getPixelColor(QPoint& point);

/*!
 * \brief updateRendererSetting updates the existing image format to the new format.
 * \param fastRendererOn flag for the 8bit image handeling.
 */
virtual void updateRendererSetting(bool fastRendererOn);

/*!
 * \brief getImageData returns the data of the current image (Note: It will allways return a ARGB32bit QImage!).
 */
virtual QImage getImageData();

/*!
 * \brief setImageData overwrites the old imageData the new imageData.
 * \param newData - represents the new imageData
 */
virtual void setImageData(const QImage& newData);

};

#endif
