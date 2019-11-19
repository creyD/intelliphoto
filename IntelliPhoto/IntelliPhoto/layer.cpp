#include "layer.h"

Layer::Layer(const int& width,const int& height){
    this->Canvas = new QImage(width, height, QImage::Format::Format_ARGB32);
}

Layer::~Layer(){
    delete this->Canvas;
}

void Layer::setPixel(const int& w,const int& h,const int& a,const int& r,const int& g,const int& b){
    QRgba64 clr;
    clr.setRed(static_cast<quint16>(r));
    clr.setGreen(static_cast<quint16>(g));
    clr.setBlue(static_cast<quint16>(b));
    clr.setAlpha(static_cast<quint16>(a));
    this->Canvas->setPixelColor(w,h,QColor(clr));
}

void Layer::loadImage(const QString& fileName){
    //load of image an specifing fileformat needs to be implemented
}

QPixmap Layer::getAsPixmap(){
    return QPixmap::fromImage(*(this->Canvas));
}

