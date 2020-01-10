#include "IntelliInputDialog.h"

IntelliInputDialog::IntelliInputDialog()
{
    setValuesOfPalette();
}

void IntelliInputDialog::Input(){
    QDialog* Dialog = new QDialog();
    QGridLayout* Layout = new QGridLayout();
    QDialogButtonBox* ButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QPushButton* Button = new QPushButton();
    Button->setFixedSize(Buttonsize);

    QPushButton* okButton = ButtonBox->button(QDialogButtonBox::Ok);
    okButton->setAutoDefault(false);
    okButton->setDefault(false);

    QPushButton* cancelButton = ButtonBox->button(QDialogButtonBox::Cancel);
    cancelButton->setAutoDefault(false);
    cancelButton->setDefault(false);

    Button->setPalette(Palette);
    okButton->setPalette(Palette);
    cancelButton->setPalette(Palette);

    Layout->addWidget(Button);
    Layout->addWidget(ButtonBox);
    Dialog->setLayout(Layout);
    Dialog->setStyleSheet("background-color:rgb(64,64,64)");
    connect(okButton, SIGNAL(clicked()),Dialog,SLOT(slotCloseEvent()));
}

void IntelliInputDialog::setValuesOfPalette(){
    Palette.setBrush(QPalette::HighlightedText, QColor(200, 10, 10));
    Palette.setBrush(QPalette::Highlight, QColor(100, 5, 5));
    Palette.setBrush(QPalette::ButtonText, QColor(255, 255, 255));
    Palette.setBrush(QPalette::Button, QColor(64, 64, 64));
    Palette.setBrush(QPalette::Window, QColor(64, 64, 64));
    Palette.setBrush(QPalette::WindowText, QColor(255, 255, 255));
    Palette.setBrush(QPalette::PlaceholderText, QColor(255, 255, 255));
    Palette.setBrush(QPalette::ToolTipText, QColor(255, 255, 255));
    Palette.setBrush(QPalette::Text, QColor(255, 255, 255));
}
