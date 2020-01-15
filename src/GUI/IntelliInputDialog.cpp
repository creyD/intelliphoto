#include "IntelliInputDialog.h"
#include <QFile>
IntelliInputDialog::IntelliInputDialog(QEventLoop* Loop, IntelliInputDialog* Dialog, QString Title, QString Label, int value, int minValue, int maxValue, int step)
{
        this->Dialog = Dialog;
		createInputBox(Title, Label, value, minValue, maxValue, step);
		createConnections(Loop);
		setValuesOfPalette();
		setInputBoxStyle();
}

void IntelliInputDialog::createInputBox(QString Title, QString Label, int value, int minValue, int maxValue, int step){
		this->Dialog = new QDialog();
		Dialog->setWindowFlags(Dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
		if(Title == nullptr) {
				Dialog->setWindowTitle("Input Box");
		}
		else{
				Dialog->setWindowTitle(Title);
		}
		Layout = new QGridLayout();
		ButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

		InputLabel = new QLabel();
		if(Label == nullptr) {
				InputLabel->setText("Width:");
		}
		else{
				InputLabel->setText(Label);
		}
		InputLabel->setFixedSize(Linesize);

		Input = new QSpinBox();
		Input->setFixedSize(Linesize);
		Input->setRange(minValue,maxValue);
		Input->setValue(value);

		okButton = ButtonBox->button(QDialogButtonBox::Ok);
		okButton->setFixedSize(Buttonsize);
		okButton->setAutoDefault(false);
		okButton->setDefault(false);

		cancelButton = ButtonBox->button(QDialogButtonBox::Cancel);
		cancelButton->setFixedSize(Buttonsize);
		cancelButton->setAutoDefault(false);
		cancelButton->setDefault(false);

		Layout->addWidget(InputLabel,1,1,1,1);
		Layout->addWidget(Input,2,1,1,1);
		Layout->addWidget(ButtonBox,3,1,1,1);
		Dialog->setLayout(Layout);
		Dialog->resize(172,94);
		Dialog->show();
}

void IntelliInputDialog::createConnections(QEventLoop* Loop){
        connect(okButton, SIGNAL(clicked()), this, SLOT(slotEingabe()));
		connect(okButton, SIGNAL(clicked()), Loop, SLOT(quit()));
		connect(cancelButton, SIGNAL(clicked()), this, SLOT(slotCloseEvent()));
		connect(cancelButton, SIGNAL(clicked()), Loop, SLOT(quit()));
}

void IntelliInputDialog::setInputBoxStyle(){
		InputLabel->setPalette(Palette);
		Input->setPalette(Palette);
		okButton->setPalette(Palette);
		cancelButton->setPalette(Palette);
		Dialog->setStyleSheet("background-color:rgb(64,64,64)");
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

void IntelliInputDialog::slotCloseEvent(){
		Dialog->close();
}

void IntelliInputDialog::slotEingabe(){
        QFile File("test.txt");

        if(!File.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug() << "Error Write to File";
        }
        std::string test = QString("%1").arg(Input->value()).toStdString();
        const char* p = test.c_str();
        File.write(p);
        File.close();

		Dialog->close();
}

void IntelliInputDialog::getIntInput(QEventLoop* Loop, IntelliInputDialog* Dialog, QString Title, QString Label, int value, int minValue, int maxValue, int step){
        this->Dialog = new IntelliInputDialog(Loop, Dialog, Title, Label, value, minValue, maxValue, step);
        Loop->exec();
}
