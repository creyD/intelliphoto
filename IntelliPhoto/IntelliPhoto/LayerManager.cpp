#include "LayerManager.h"

LayerManager::LayerManager(){
    //setup the label for the image
    this->imgLabel = new QLabel("");
}

LayerManager::~LayerManager(){
    delete this->imgLabel;
    for(auto element:Ebenen){
        delete element;
    }
}

int LayerManager::getLayerCount(){
    return static_cast<int>(this->Ebenen.size());
}

void LayerManager::setLayerVisbility(int idx, int alpha){
    //current alpha is ignored, just one image is shown
    //all images should hold on to their current alpha
    for(auto &element: this->MetaEbenen){
        element.a=0;
    }
    MetaEbenen[static_cast<size_t>(idx)].a=255;
}

void LayerManager::activateLayer(int idx){
    //all images should blurr an active layer should show
    for(auto& element: this->MetaEbenen){
        element.a = 0;
    }
    MetaEbenen[static_cast<size_t>(idx)].a=255;
}

void LayerManager::goLayerUp(){
    //at current state, sets the alpha of the higher one up
    for(size_t i=0; i<static_cast<size_t>(this->getLayerCount()); i++){
        if(this->MetaEbenen[i].a==255){
            if(i==static_cast<size_t>(this->getLayerCount())-1){
                return;
            }
            MetaEbenen[i].a=0;
            MetaEbenen[i+1].a=255;
            return;
        }
    }
}

void LayerManager::goLayerDown(){
    //at current state, sets the alpha of the higher one down
    for(size_t i=0; i<static_cast<size_t>(this->getLayerCount()); i++){
        if(this->MetaEbenen[i].a==255){
            if(i==0){
                return;
            }
            MetaEbenen[i].a=0;
            MetaEbenen[i-1].a=255;
            return;
        }
    }
}

void LayerManager::AddLayerAfer(int idx){
    //layer dimension needs to be asked, maybe in seperat window
    Layer* newLayer = new Layer(600,400);

    //hardcoded layer for test sake
    for(int i=0; i<600; i++){
        for(int j=0; j<400; j++){
            newLayer->setPixel(i,j,255,0,0,255);
        }
    }

    for(int i=0; i<300; i++){
        for(int j = 0; j<5; j++)
            newLayer->setPixel(i,j,0,255,255,255);
    }
    maxWidth=100;
    maxHeight=100;


    Ebenen.insert(Ebenen.begin()+idx, newLayer);
    MetaEbenen.insert(MetaEbenen.begin()+idx, EbenenMetaDaten(0,0,0));
}

void LayerManager::DeleteLayer(int idx){
    Ebenen.erase(Ebenen.begin()+idx);
    MetaEbenen.erase(MetaEbenen.begin()+idx);
}

QLabel* LayerManager::getDisplayable(){

    //Tranzparenz der Ebenen muss möglich sein
    QPixmap aMap;
    for(size_t i=0; i<static_cast<size_t>(this->getLayerCount()); i++){
        if(MetaEbenen[i].a==255){
            aMap = Ebenen[i]->getAsPixmap();
            break;
        }
    }

    this->imgLabel->setPixmap(aMap);
    return imgLabel;
}

void LayerManager::floodFillLayer(int r, int g, int b){
    for(size_t i=0; i< static_cast<size_t>(this->getLayerCount()); i++){
           if(MetaEbenen[i].a==255){
               Ebenen[i]->floodFill(r,g,b);
               this->UpdateLabel();
               return;
           }
    }
}

void LayerManager::UpdateLabel(){
    //Tranzparenz der Ebenen muss möglich sein
    QPixmap aMap;
    for(size_t i=0; i<static_cast<size_t>(this->getLayerCount()); i++){
        if(MetaEbenen[i].a==255){
            aMap = Ebenen[i]->getAsPixmap();
            break;
        }
    }

    this->imgLabel->setPixmap(aMap);
}
