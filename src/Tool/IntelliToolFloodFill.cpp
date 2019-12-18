#include "IntelliToolFloodFill.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"
#include "QInputDialog"
#include <functional>
#include <queue>

IntelliToolFloodFill::IntelliToolFloodFill(PaintingArea* Area, IntelliColorPicker* colorPicker)
    :IntelliTool(Area, colorPicker){
}

IntelliToolFloodFill::~IntelliToolFloodFill(){

}


void IntelliToolFloodFill::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolFloodFill::onMouseRightReleased(int x, int y){
    IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolFloodFill::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    QColor oldColor = this->Active->image->getPixelColor(x,y);
    std::queue<QPoint> Q;
    Q.push(QPoint(x,y));
    QColor newColor = this->colorPicker->getFirstColor();
    Canvas->image->drawPixel(QPoint(x,y),newColor);
    while(!Q.empty()){
        QPoint Front = Q.front();
        Q.pop();
        if((Front.x()+1 < Canvas->width)&&
           (Active->image->getPixelColor(Front.x()+1,Front.y()) == oldColor)&&
           (Canvas->image->getPixelColor(Front.x()+1,Front.y()) != newColor)){
            Canvas->image->drawPixel(QPoint(Front.x()+1, Front.y()),newColor);
            Q.push(QPoint(Front.x()+1,Front.y()));
        }
        if((Front.x()-1 >= 0)&&
           (Active->image->getPixelColor(Front.x()-1,Front.y()) == oldColor)&&
           (Canvas->image->getPixelColor(Front.x()-1,Front.y()) != newColor)){
            Canvas->image->drawPixel(QPoint(Front.x()-1, Front.y()),newColor);
            Q.push(QPoint(Front.x()-1,Front.y()));
        }
        if((Front.y()+1 < Canvas->hight)&&
           (Active->image->getPixelColor(Front.x(),Front.y()+1) == oldColor)&&
           (Canvas->image->getPixelColor(Front.x(),Front.y()+1) != newColor)){
            Canvas->image->drawPixel(QPoint(Front.x(), Front.y()+1),newColor);
            Q.push(QPoint(Front.x(),Front.y()+1));
        }
        if((Front.y()-1 >= 0)&&
           (Active->image->getPixelColor(Front.x(),Front.y()-1) == oldColor)&&
           (Canvas->image->getPixelColor(Front.x(),Front.y()-1) != newColor)){
            Canvas->image->drawPixel(QPoint(Front.x(), Front.y()-1),newColor);
            Q.push(QPoint(Front.x(),Front.y()-1));
        }
    }


    /* std::function<void(int,int, LayerObject*, LayerObject*, QColor, QColor)> depthsearch =
        [&depthsearch](int x, int y,LayerObject* Active, LayerObject* Canvas, QColor oldColor, QColor newColor){
            if((x >= 0) && (y >= 0) && (x < Canvas->width) && (y < Canvas->hight)){
                if(Active->image->getPixelColor(x,y) == oldColor){
                    Canvas->image->drawPoint(QPoint(x,y),newColor,1);
                    depthsearch(x-1,y,Active,Canvas,oldColor,newColor);
                    depthsearch(x,y+1,Active,Canvas,oldColor,newColor);
                    depthsearch(x+1,y,Active,Canvas,oldColor,newColor);
                    depthsearch(x,y-1,Active,Canvas,oldColor,newColor);
                }
            }
        };
    depthsearch(x,y,Active,Canvas,oldColor,this->colorPicker->getFirstColor());
    */
    Canvas->image->calculateVisiblity();


}

void IntelliToolFloodFill::onMouseLeftReleased(int x, int y){
    IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolFloodFill::onWheelScrolled(int value){
    IntelliTool::onWheelScrolled(value);

}

void IntelliToolFloodFill::onMouseMoved(int x, int y){
    IntelliTool::onMouseMoved(x,y);
}
