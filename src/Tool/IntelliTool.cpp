#include "IntelliTool.h"
#include "Layer/PaintingArea.h"

IntelliTool::IntelliTool(PaintingArea* Area, IntelliColorPicker* colorPicker){
		this->Area=Area;
		this->colorPicker=colorPicker;
}


IntelliTool::~IntelliTool(){

}

void IntelliTool::onMouseRightPressed(int x, int y){
		if(isDrawing) {
				isDrawing=false;
				this->deleteToolLayer();
		}
}

void IntelliTool::onMouseRightReleased(int x, int y){
		//optional for tool
}

void IntelliTool::onMouseLeftPressed(int x, int y){
		this->isDrawing=true;
		//create drawing layer
		this->createToolLayer();
		Canvas->image->calculateVisiblity();
}

void IntelliTool::onMouseLeftReleased(int x, int y){
		if(isDrawing) {
				isDrawing=false;
				this->mergeToolLayer();
				this->deleteToolLayer();
				activeLayer->image->calculateVisiblity();
		}
}

void IntelliTool::onMouseMoved(int x, int y){
		if(isDrawing)
				Canvas->image->calculateVisiblity();
}

void IntelliTool::onWheelScrolled(int value){
		//if needed for future general tasks implement in here
}

void IntelliTool::createToolLayer(){
		Area->createTempTopLayer(Area->activeLayer);
        this->activeLayer=&Area->layerBundle[static_cast<unsigned long long>(Area->activeLayer)];
        this->Canvas=&Area->layerBundle[static_cast<unsigned long long>(Area->activeLayer+1)];
}

void IntelliTool::mergeToolLayer(){
		QColor clr_0;
		QColor clr_1;
		for(int y=0; y<activeLayer->height; y++) {
				for(int x=0; x<activeLayer->width; x++) {
						clr_0=activeLayer->image->imageData.pixelColor(x,y);
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

						activeLayer->image->imageData.setPixelColor(x, y, clr_0);
				}
		}
}

void IntelliTool::deleteToolLayer(){
		Area->deleteLayer(Area->activeLayer+1);
		this->Canvas=nullptr;
}

IntelliTool::Tooltype IntelliTool::getTooltype(){
    return ActiveType;
}

bool IntelliTool::getIsDrawing(){
    return isDrawing;
}
