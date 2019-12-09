#ifndef IntelliPhotoGui_H
#define IntelliPhotoGui_H

#include <QList>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>

// PaintingArea used to paint the image
class PaintingArea;

class IntelliPhotoGui : public QMainWindow
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT
public:
    IntelliPhotoGui();

protected:
    // Function used to close an event
    void closeEvent(QCloseEvent *event) override;

// The events that can be triggered
private slots:
    void open();
    void save();
    void newLayer();
    void deleteLayer();
    void about();

    void onClearedPressed();
    void onActivePressed();
    void onSetAlpha();
    void onMoveUp();
    void onMoveDown();
    void onMoveLeft();
    void onMoveRight();
    void onMoveLayerUp();
    void onMoveLayerDown();

private:
    // Will tie user actions to functions
    void createActions();
    void createMenus();
    //setup GUI elements
    void createGui();
    //set style of the GUI
    void setIntelliStyle();


    // Will check if changes have occurred since last save
    bool maybeSave();
    // Opens the Save dialog and saves
    bool saveFile(const QByteArray &fileFormat);

    // What we'll draw on
    PaintingArea* paintingArea;

    // The menu widgets
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *layerMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;

    // All the actions that can occur
    QAction *openAct;
    QAction *exitAct;

    QAction *newLayerAct;
    QAction *deleteLayerAct;
    QAction *deleteActiveLayerAct;

    QAction *aboutAct;
    QAction *aboutQtAct;

    QAction* clearedActions;
    QAction* setActiveAction;
    QAction* setAlphaAction;
    QAction* moveUpAction;
    QAction* moveDownAction;
    QAction* moveLeftAction;
    QAction* moveRightAction;
    QAction* moveLayerUpAction;
    QAction* moveLayerDownAction;

    // Actions tied to specific file formats
    QList<QAction *> saveAsActs;

    //main GUI elements
    QWidget* centralGuiWidget;
    QGridLayout *mainLayout;

};

#endif
