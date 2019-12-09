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
signals:
    void sendClearColor(int r, int g, int b);
    void sendActiveLayer(int a);
    void sendAlpha(int a);
    void moveUp(int a);
    void moveDown(int a);
    void moveRight(int a);
    void moveLeft(int a);
    void moveLayerUp();
    void moveLayerDown();

public:
    IntelliPhotoGui();
protected:
    // Function used to close an event
    void closeEvent(QCloseEvent *event) override;

// The events that can be triggered
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
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
    QMenu *helpMenu;


    // All the actions that can occur
    QAction *openAct;

    // Actions tied to specific file formats
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *clearScreenAct;
    QAction *newLayerAct;
    QAction *deleteLayerAct;
    QAction *deleteActiveLayerAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    //main GUI elements
    QWidget* centralGuiWidget;
    QGridLayout *mainLayout;
    QPushButton *clearButton;

    QLabel *RedLabel;
    QLabel *GreenLabel;
    QLabel *BlueLabel;
    QLineEdit *RedEdit;
    QLineEdit *GreenEdit;
    QLineEdit *BlueEdit;

    QPushButton *selectActiveButton;
    QLabel *selectActiveLabel;
    QLineEdit *selectActiveEdit;

    QPushButton *setAlphaButton;
    QLabel *setAlphaLabel;
    QLineEdit *setAlphaEdit;

    QPushButton *moveActiveUpButton;
    QPushButton *moveActiveDownButton;
    QPushButton *moveActiveLeftButton;
    QPushButton *moveActiveRightButton;

    QPushButton *layerMoveActiveDownButton;
    QPushButton *layerMoveActiveUpButton;

};

#endif
