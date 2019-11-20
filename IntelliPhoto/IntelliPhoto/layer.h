#ifndef LAYER_H
#define LAYER_H
#include<QImage>
#include<QPixmap>
#include<QString>

class Layer{
private:
    //pixelmap for the image, used because of performance and api reasons
    QImage* Canvas;

    //width of the image
    int width;

    //height of the imahe
    int height;
public:
    //setup everything for the image
    Layer(const int& width,const int& height);
    ~Layer();

    //set one pixel with rgba values
    void setPixel(const int& w,const int& h,const int& r,const int& g,const int& b, const int& a);

    //load an image to the canvas
    void loadImage(const QString& fileName);

    //flood fills canvas
    void floodFill(int r, int g, int b);

    //return the image as QPixmap
    QPixmap getAsPixmap();
};

#endif // LAYER_H
