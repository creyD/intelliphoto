#include "IntelliInputDialog.h"
#include <QFile>


IntelliInputDialog::IntelliInputDialog(QEventLoop* Loop, QString Title, QString Label, int value, int minValue, int maxValue, int step)
{
		createInputBox(Title, Label, value, minValue, maxValue, step);
		createConnections(Loop);
		setValuesOfPalette();
		setInputBoxStyle();
        Loop->exec();
}

void IntelliInputDialog::createInputBox(QString Title, QString Label, int value, int minValue, int maxValue, int step){
        this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
		if(Title == nullptr) {
                this->setWindowTitle("Input Box");
		}
		else{
                this->setWindowTitle(Title);
		}
        this->Layout = new QGridLayout();
        this->ButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        this->InputLabel = new QLabel();
		if(Label == nullptr) {
                this->InputLabel->setText("Width:");
		}
		else{
                this->InputLabel->setText(Label);
		}
        this->InputLabel->setFixedSize(Linesize);

        this->Input = new QSpinBox();
        this->Input->setFixedSize(Linesize);
        this->Input->setRange(minValue,maxValue);
        this->Input->setValue(value);

        this->okButton = ButtonBox->button(QDialogButtonBox::Ok);
        this->okButton->setFixedSize(Buttonsize);
        this->okButton->setAutoDefault(false);
        this->okButton->setDefault(false);

        this->cancelButton = ButtonBox->button(QDialogButtonBox::Cancel);
        this->cancelButton->setFixedSize(Buttonsize);
        this->cancelButton->setAutoDefault(false);
        this->cancelButton->setDefault(false);

		Layout->addWidget(InputLabel,1,1,1,1);
		Layout->addWidget(Input,2,1,1,1);
		Layout->addWidget(ButtonBox,3,1,1,1);
        this->setLayout(Layout);
        this->resize(172,94);
        this->show();
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
        this->setStyleSheet("background-color:rgb(64,64,64)");
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
        this->close();
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

        this->close();
}
