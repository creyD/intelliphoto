#ifndef LAYER_H
#define LAYER_H
#include<QImage>
#include<QPixmap>
#include<QString>

class Layer{
private:
    QImage* Canvas;
    int width;
    int height;
public:
    Layer(const int& width,const int& height);
    ~Layer();
    void setPixel(const int& w,const int& h,const int& a,const int& r,const int& g,const int& b);
    void loadImage(const QString& fileName);
    QPixmap getAsPixmap();
};

#endif // LAYER_H
