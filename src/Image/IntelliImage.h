#ifndef INTELLIIMAGE_H
#define INTELLIIMAGE_H

#include <QImage>
#include <QPoint>
#include <QColor>
#include <QSize>
#include <QWidget>
#include <vector>

/*!
 * \brief The Types, which an Image can be.
 */
enum class ImageType {
		Raster_Image,
		Shaped_Image
};

class IntelliTool;

/*!
 * \brief An abstract class which manages the basic IntelliImage operations.
 */
class IntelliImage {
friend IntelliTool;
protected:
void resizeImage(QImage*image, const QSize &newSize);

/*!
 * \brief The underlying image data.
 */
QImage imageData;
public:
/*!
 * \brief The Construcor of the IntelliImage. Given the Image dimensions.
 * \param weight    - The weight of the Image.
 * \param height    - The height of the Image.
 */
IntelliImage(int weight, int height);

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
virtual QImage getDisplayable(int alpha=255) = 0;

/*!
 * \brief A function that copys all that returns a [allocated] Image
 * \return A [allocated] Image with all the properties of the instance.
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

/*!
 * \brief A function that loads and sclaes an image to the fitting dimensions.
 * \param fileName  - The path+name of the image which to loaded.
 * \return True if the image could be loaded, false otherwise.
 */
virtual bool loadImage(const QString &fileName);

/*!
 * \brief A function that returns the pixelcolor at a certain point
 * \param point - The point from whcih to get the coordinates.
 * \return The color of the Pixel as QColor.
 */
virtual QColor getPixelColor(QPoint& point);
};

#endif
