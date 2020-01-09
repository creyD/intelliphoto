#include "IntelliToolPlain.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"

IntelliToolPlainTool::IntelliToolPlainTool(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings)
        : IntelliTool(Area, colorPicker, Toolsettings){
        this->ActiveType = Tooltype::PLAIN;
}

IntelliToolPlainTool::~IntelliToolPlainTool(){
        IntelliTool::onMouseRightPressed(0,0);
}

void IntelliToolPlainTool::onMouseLeftPressed(int x, int y){
		IntelliTool::onMouseLeftPressed(x,y);
		this->Canvas->image->drawPlain(colorPicker->getFirstColor());
		Canvas->image->calculateVisiblity();
}

void IntelliToolPlainTool::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolPlainTool::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPlainTool::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolPlainTool::onMouseMoved(int x, int y){
		IntelliTool::onMouseMoved(x,y);
}

void IntelliToolPlainTool::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
}
