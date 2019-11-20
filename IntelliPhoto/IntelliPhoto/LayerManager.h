#ifndef CANVAS_H
#define CANVAS_H
#include"layer.h"

#include<vector>
#include <QLabel>
#include <QWidget>




class LayerManager{
private:
    //Uses to handle the Meta Data of each layer in comparission to 'global' propteries
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
    //max width of the layer (max(EbenenMetaDaten.x+Layer.width))
    int maxWidth;
    //max width of the layer (max(EbenenMetaDaten.y+Layer.height))
    int maxHeight;

    // The label where the image is shown
    QLabel* imgLabel;

    //all the possible layers in one container
    std::vector<Layer*> Ebenen;

    //all the meta data parallel to Ebenen Container
    std::vector<EbenenMetaDaten> MetaEbenen;

    //updates the display
    void UpdateLabel();
public:
    LayerManager();
    ~LayerManager();

    //gets the count of layers
    int getLayerCount();

    //set one layer to a given alpha value
    void setLayerVisbility(int idx, int alpha);

    //activates one layer to work on it
    void activateLayer(int idx);

    //changes the active layer one up
    void goLayerUp();

    //changes the active layer one down
    void goLayerDown();

    //adds a new layer after (on top of) the given idx (-1 create bottom layer)
    void AddLayerAfer(int idx);

    //delets a layer at the given index
    void DeleteLayer(int idx);

    //fill active Layer
    void floodFillLayer(int r, int g, int b);

    //returns the output ready label
    QLabel* getDisplayable();
};

#endif // CANVAS_H
