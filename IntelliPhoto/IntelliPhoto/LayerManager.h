#ifndef CANVAS_H
#define CANVAS_H
#include"layer.h"

#include<vector>
#include <QLabel>




class LayerManager{
private:
    struct EbenenMetaDaten{
        unsigned int x;
        unsigned int y;
        unsigned int a;
        EbenenMetaDaten(unsigned int x, unsigned int y, unsigned int a){
            this->x = x;
            this->y = y;
            this->a = a;
        }
    };
    int maxWidth;
    int maxHeight;

    QLabel* imgLabel;
    std::vector<Layer*> Ebenen;
    std::vector<EbenenMetaDaten> MetaEbenen;
public:
    LayerManager();
    ~LayerManager();

    int getLayerCount();
    void setLayerVisbility(int idx, int alpha);
    void activateLayer(int idx);
    void goLayerUp();
    void goLayerDown();
    void AddLayerAfer(int idx);
    void DeleteLayer(int idx);
    QLabel* getDisplayable();
};

#endif // CANVAS_H
