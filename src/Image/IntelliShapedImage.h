#ifndef INTELLISHAPE_H
#define INTELLISHAPE_H

#include"Image/IntelliRasterImage.h"
#include<vector>
#include"IntelliHelper/IntelliHelper.h"

/*!
 * \brief The IntelliShapedImage manages a Shapedimage.
 */
class IntelliShapedImage : public IntelliRasterImage{
    friend IntelliTool;
private:
    /*!
     * \brief The Triangulation of the Polygon. Saved here for performance reasons.
     */
    std::vector<Triangle> triangles;

    /*!
     * \brief Calculates the visibility based on the underlying polygon.
     */
    virtual void calculateVisiblity() override;
protected:

    /*!
     * \brief The Vertices of The Polygon. Needs to be a planar Polygon.
     */
    std::vector<QPoint> polygonData;
public:
    /*!
     * \brief The Construcor of the IntelliShapedImage. Given the Image dimensions.
     * \param weight    - The weight of the Image.
     * \param height    - The height of the Image.
     */
    IntelliShapedImage(int weight, int height);

    /*!
     * \brief An Destructor.
     */
    virtual ~IntelliShapedImage() override;

    /*!
     * \brief A function returning the displayable ImageData in a requested transparence and size.
     * \param displaySize   - The size, in whcih the Image should be displayed.
     * \param alpha         - The maximum alpha value, a pixel can have.
     * \return A QImage which is ready to be displayed.
     */
    virtual QImage getDisplayable(const QSize& displaySize, int alpha=255) override;

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
     * \brief A function that returns the Polygondata if existent.
     * \return The Polygondata if existent.
     */
    virtual std::vector<QPoint> getPolygonData() override{return polygonData;}

    /*!
     * \brief A function that sets the data of the visible Polygon.
     * \param polygonData   - The Vertices of the Polygon. Just Planar Polygons are allowed.
     */
    virtual void setPolygon(const std::vector<QPoint>& polygonData) override;
};

#endif
