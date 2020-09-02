#include "stdafx.h"
#include "W_FastWindow.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		���ٴ��� ����.cpp
		�汾��		v1.01
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		������д�������Ĵ��ڡ�

		ʹ�÷�����
				>׼��class
					this->local_class = C_FastClass("Ŀ��ģ��");		
					this->local_class.addDouble("λ��", "0.0", true);
					this->local_class.addDouble("����", "0.0", true);
					this->local_class.addDouble("����", "0.0");
					this->local_class.addDouble("γ��", "0.0");
				>������д����
					W_FastWindow d(this);
					d.setDataInAddMode(this->local_class);
					if (d.exec() == QDialog::Accepted ) {
						QJsonObject p = d.getData();
						this->local_dataList.append(p);
					}
-----==========================================================-----
*/

W_FastWindow::W_FastWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_fastForm = new P_FastForm(ui.widget_params);
	this->local_class = C_FastClass("");
	this->local_data = QJsonObject();

	//-----------------------------------
	//----�¼���
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &W_FastWindow::acceptData);

	//-----------------------------------
	//----��ʼ��ui
	TTool::_chinese_(ui.buttonBox);
}

W_FastWindow::~W_FastWindow(){
}


/*-------------------------------------------------
		�س��¼�����
*/
void W_FastWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
		this->focusNextChild();
	}else{
		QDialog::keyPressEvent(event);
	}
}



/*-------------------------------------------------
		���� - �������ݣ���ӣ�
*/
void W_FastWindow::setDataInAddMode(C_FastClass c_f){
	this->setWindowTitle("���" + c_f.getClassNameShowing());
	this->m_fastForm->prepareFastClass(c_f);
	this->m_fastForm->prepareQSpacerItem();
	this->m_fastForm->rebuildUI();

	this->local_data = QJsonObject();
	this->local_class = c_f;
	this->isAddMode = true;
	this->putDataToUi();
}
/*-------------------------------------------------
		���� - �������ݣ��޸ģ�
*/
void W_FastWindow::setDataInModifyMode(C_FastClass c_f, QJsonObject p) {
	this->setWindowTitle("�༭" + c_f.getClassNameShowing());
	this->m_fastForm->prepareFastClass(c_f);
	this->m_fastForm->prepareQSpacerItem();
	this->m_fastForm->rebuildUI();

	this->local_data = p;
	this->local_class = c_f;
	this->isAddMode = false;
	this->putDataToUi();
}

/*-------------------------------------------------
		���� - ȡ������
*/
QJsonObject W_FastWindow::getData(){
	return this->local_data;
};
/*-------------------------------------------------
		���� - �������� -> ui����
*/
void W_FastWindow::putDataToUi() {
	this->m_fastForm->setJsonObjectAutoDefault(this->local_data);
};
/*-------------------------------------------------
		���� - ui���� -> ��������
*/
void W_FastWindow::putUiToData() {
	this->local_data = this->m_fastForm->getJsonObject();
};
/*-------------------------------------------------
		���� - �ύ���ݣ�У�飩
*/
void W_FastWindow::acceptData(){
	this->putUiToData();

	// > ��У��
	if (this->m_fastForm->isAllNotNullConform() == false ) {
		QMessageBox::warning(this, "��ʾ", "�������Ϊ�ա�");
		return;
	}
	// > �ظ�У��
	//if (isAddMode && S_SourceDataContainer::getInstance()->hasTagName(local_SourceVoltage.name)) {
	//	QMessageBox::warning(this, "��ʾ", "��ǩ�Ѵ��ڡ�");
	//	return;
	//}

	emit acceptDataSignal(this->isAddMode, this->local_data);
	this->accept();
};