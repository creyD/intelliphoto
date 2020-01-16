#include "IntelliInputDialog.h"

IntelliInputDialog::IntelliInputDialog(QString Title, QString Label, int value, int minValue, int maxValue, int step, bool* ok)
{
		this->valueInt = value;
		this->notClosed = ok;
		if(notClosed != nullptr) {
				*notClosed = false;
		}
		createInputBox(Title, Label, value, minValue, maxValue, step);
		createConnections();
		setInputBoxStyle();
		this->exec();
}

int IntelliInputDialog::getInt(QString Title, QString Label, int value, int minValue, int maxValue, int step, bool* ok){
		IntelliInputDialog dialog(Title, Label, value, minValue, maxValue, step, ok);
		return dialog.valueInt;
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
		this->Input->setSingleStep(step);
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

void IntelliInputDialog::createConnections(){
		connect(okButton, SIGNAL(clicked()), this, SLOT(slotEingabe()));
		connect(cancelButton, SIGNAL(clicked()), this, SLOT(slotCloseEvent()));
}

void IntelliInputDialog::setInputBoxStyle(){
		this->setStyleSheet("color: white;" "background-color: rgb(64, 64, 64);" "selection-color: rgb(200, 10, 10);" "selection-background-color: rgb(64, 64, 64);");
}

void IntelliInputDialog::slotCloseEvent(){
		this->close();
}

void IntelliInputDialog::slotEingabe(){
		valueInt = QString("%1").arg(Input->value()).toInt();
		if(notClosed != nullptr) {
				*notClosed = true;
		}
		this->close();
}
