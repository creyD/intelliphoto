#include "layer.h"

Layer::Layer(const int& width,const int& height){
    this->Canvas = new QImage(width, height, QImage::Format_RGB32);
    this->width=width;
    this->height=height;
}

Layer::~Layer(){
    delete this->Canvas;
}

void Layer::setPixel(const int& w,const int& h, const int& r,const int& g,const int& b, const int& a){
    this->Canvas->setPixelColor(w,h,QColor(r,g,b,a));
}

void Layer::loadImage(const QString& fileName){
    //load of image an specifing fileformat needs to be implemented
}

QPixmap Layer::getAsPixmap(){
    return QPixmap::fromImage(*(this->Canvas));
}


void Layer::floodFill(int r, int g, int b){
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            this->Canvas->setPixelColor(i,j,QColor(r,g,b,255));
        }
    }
}
