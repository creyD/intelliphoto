#include"IntelliTool.h"
#include"Layer/PaintingArea.h"

IntelliTool::IntelliTool(PaintingArea* Area){
    this->Area=Area;
}


IntelliTool::~IntelliTool(){

}

void IntelliTool::onMouseRightPressed(int x, int y){
    if(drawing){
        drawing=false;
        this->deleteToolLayer();
    }
}

void IntelliTool::onMouseRightReleased(int x, int y){
    //optional for tool
}

void IntelliTool::onMouseLeftPressed(int x, int y){
    this->drawing=true;
    //create drawing layer
    this->createToolLayer();

}

void IntelliTool::onMouseLeftReleased(int x, int y){
    if(drawing){
        drawing=false;
        this->mergeToolLayer();
        this->deleteToolLayer();
    }
}

void IntelliTool::onMouseMoved(int x, int y){
    //optional for tool
}

void IntelliTool::createToolLayer(){
    Area->createTempLayerAfter(Area->activeLayer);
    this->Active=&Area->layerBundle[Area->activeLayer];
    this->Canvas=&Area->layerBundle[Area->activeLayer+1];
}

void IntelliTool::mergeToolLayer(){
    QColor clr_0;
    QColor clr_1;
    for(int y=0; y<Active->hight; y++){
        for(int x=0; x<Active->width; x++){
            clr_0=Active->image->imageData.pixelColor(x,y);
            clr_1=Canvas->image->imageData.pixelColor(x,y);
            float t = static_cast<float>(clr_1.alpha())/255.f;
            int r =static_cast<int>(static_cast<float>(clr_1.red())*(t)+static_cast<float>(clr_0.red())*(1.f-t)+0.5f);
            int g =static_cast<int>(static_cast<float>(clr_1.green())*(t)+static_cast<float>(clr_0.green())*(1.f-t)+0.5f);
            int b =static_cast<int>(static_cast<float>(clr_1.blue())*(t)+static_cast<float>(clr_0.blue()*(1.f-t))+0.5f);
            int a =std::min(clr_0.alpha()+clr_1.alpha(), 255);
            clr_0.setRed(r);
            clr_0.setGreen(g);
            clr_0.setBlue(b);
            clr_0.setAlpha(a);

            Active->image->imageData.setPixelColor(x, y, clr_0);
        }
    }
}

void IntelliTool::deleteToolLayer(){
    Area->deleteLayer(Area->activeLayer+1);
    this->Canvas=nullptr;
}
