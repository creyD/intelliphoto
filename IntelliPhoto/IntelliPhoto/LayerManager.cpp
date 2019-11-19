#include "LayerManager.h"

LayerManager::LayerManager(){
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
    for(auto &element: this->MetaEbenen){
        element.a=0;
    }
    MetaEbenen[static_cast<size_t>(idx)].a=255;
}

void LayerManager::activateLayer(int idx){
    for(auto& element: this->MetaEbenen){
        element.a = 0;
    }
    MetaEbenen[static_cast<size_t>(idx)].a=255;
}

void LayerManager::goLayerUp(){
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
    Layer* newLayer = new Layer(100,100);
    Ebenen.insert(Ebenen.begin()+idx, newLayer);
}

void LayerManager::DeleteLayer(int idx){
    Ebenen.erase(Ebenen.begin()+idx);
}

QLabel* LayerManager::getDisplayable(){
    //Tranzparenz der Ebenen muss möglich sein
    QPixmap Map(maxWidth, maxHeight);
    for(size_t i=0; i<static_cast<size_t>(this->getLayerCount()); i++){
        if(MetaEbenen[i].a==255){
            Map = Ebenen[i]->getAsPixmap();
            break;
        }
    }
    this->imgLabel->setPixmap(Map);
    return imgLabel;
}
