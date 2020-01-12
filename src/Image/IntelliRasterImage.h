#ifndef INTELLIRASTER_H
#define INTELLIRASTER_H

#include "Image/IntelliImage.h"

//for unit testing
class UnitTest;

/*!
 * \brief The IntelliRasterImage manages a RASTERIMAGE.
 */
class IntelliRasterImage : public IntelliImage {
    friend UnitTest;
friend IntelliTool;
protected:
/*!
 * \brief A function that calculates the visibility of the image if a polygon is given. [does nothing in RASTERIMAGE]
 */
virtual void calculateVisiblity() override;
public:
/*!
 * \brief The Construcor of the IntelliRasterImage. Given the Image dimensions.
 * \param width    - The width of the Image.
 * \param height    - The height of the Image.
 * \param fastRendererOn    - Represents the flag for 8bit picture handelling.
 */
IntelliRasterImage(int width, int height, bool fastRendererOn);

/*!
 * \brief An Destructor.
 */
virtual ~IntelliRasterImage() override;

/*!
 * \brief A function returning the displayable ImageData in a requested transparence and size.
 * \param displaySize   - The size, in whcih the Image should be displayed.
 * \param alpha         - The maximum alpha value, a pixel can have.
 * \return A QImage which is ready to be displayed.
 */
virtual QImage getDisplayable(const QSize& displaySize,int alpha) override;

/**
 * @brief A function returning the displayable ImageData in a requested transparence and it's standart size.
 * @param alpha - The maximum alpha value, a pixel can have.
 * @return A QImage which is ready to be displayed.
 */
virtual QImage getDisplayable(int alpha=255) override;

/*!
 * \brief A function that copys all that returns a [allocated] Image
 * \return A [allocated] Image with all the properties of the instance.
 */
virtual IntelliImage* getDeepCopy() override;

/*!
 * \brief An abstract function that sets the data of the visible Polygon, if needed.
 * \param polygonData   - The Vertices of the Polygon. Nothing happens.
 */
virtual void setPolygon(const std::vector<QPoint>& polygonData) override;
};

#endif
