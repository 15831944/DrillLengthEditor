#include "stdafx.h"
#include "W_FastListWindow.h"

#include "Source/Utils/common/TTool.h"
#include "w_FastWindow.h"

/*
-----==========================================================-----
		�ࣺ		�����б� ����.cpp
		�汾��		v1.01
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���ݱ༭�Ŀ����б���ơ�
		
		Ŀ�꣺		1.ճ��ĳ��ǵ���һ�
					  ����ĳ���һ�
					2.���롢������
		
		˵����		1.�����б������ ���ٴ��ڣ�ֻ���ÿ����б���������ȫ����д�������ݡ�

		ʹ�÷�����
				>׼��class
					this->local_class = C_FastClass("Ŀ��ģ��");		
					this->local_class.addDouble("λ��", "0.0", true);
					this->local_class.addDouble("����", "0.0", true);
					this->local_class.addDouble("����", "0.0");
					this->local_class.addDouble("γ��", "0.0");
				>������д�б�
					W_FastListWindow d(this);
					d.setData(this->local_class, this->local_data);
					if (d.exec() == QDialog::Accepted) {
						this->local_data = d.getData();
					}
-----==========================================================-----
*/

W_FastListWindow::W_FastListWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->local_dataList = QList<QJsonObject>();
	this->local_class = C_FastClass("");

	//-----------------------------------
	//----�¼���
	connect(ui.pushButton_add, &QPushButton::clicked, this, &W_FastListWindow::addOneRow);
	connect(ui.pushButton_modify, &QPushButton::clicked, this, &W_FastListWindow::modifyOneRow);
	connect(ui.pushButton_delete, &QPushButton::clicked, this, &W_FastListWindow::deleteOneRow);
	connect(ui.tableWidget, &QTableWidget::itemSelectionChanged, this, &W_FastListWindow::modifyOneRow);		//˫���༭��
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &W_FastListWindow::acceptData);

	//-----------------------------------
	//----��ʼ��ui
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//����Ӧ��С
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);				//����ģʽ
	TTool::_chinese_(ui.buttonBox);
}

W_FastListWindow::~W_FastListWindow(){
}


/*-----------------------------------
		���
*/
void W_FastListWindow::addOneRow() {
	W_FastWindow d(this);
	d.setDataInAddMode(this->local_class);
	if (d.exec() == QDialog::Accepted ) {
		QJsonObject p = d.getData();
		local_dataList.append(p);
		this->refreshTable();
	}

}
/*-----------------------------------
		�༭
*/
void W_FastListWindow::modifyOneRow() {
	QList<QTableWidgetSelectionRange> range = ui.tableWidget->selectedRanges();
	if (range.size() == 0) {
		QMessageBox::warning(this, ("��ʾ"), ("����ѡ����Ҫ�༭��һ�С�"));
		return;
	}
	int pos = range.at(0).topRow();

	QJsonObject obj = local_dataList.at(pos);
	W_FastWindow d(this);
	d.setDataInModifyMode(this->local_class, obj);
	if (d.exec() == QDialog::Accepted) {
		QJsonObject p = d.getData();
		local_dataList.replace(pos, p);
		this->refreshTable();
	}
}
/*-----------------------------------
		ɾ��
*/
void W_FastListWindow::deleteOneRow() {
	QList<QTableWidgetSelectionRange> range = ui.tableWidget->selectedRanges();
	if (range.size() == 0) {
		QMessageBox::warning(this, ("��ʾ"), ("����ѡ����Ҫɾ����һ�С�"));
		return;
	}
	int pos = range.at(0).topRow();

	local_dataList.removeAt(pos);

	this->refreshTable();
}
/*-----------------------------------
		ˢ�±��
*/
void W_FastListWindow::refreshTable() {

	this->local_class.fillDataInTableWidget(ui.tableWidget,this->local_dataList);

}


/*-------------------------------------------------
		���� - �������ݣ��޸ģ�
*/
void W_FastListWindow::setData(C_FastClass c_f, QList<QJsonObject> p) {

	// > ��������
	this->setWindowTitle(c_f.getClassNameShowing() + "�б�");
	ui.groupBox->setTitle(c_f.getClassNameShowing());

	// > ���ڴ�С
	int c_count = c_f.getConvertedParamList().count();
	int r_count = p.count();
	int ww = 350 + c_count * 35;
	if (ww > 1000){ ww = 1000; }
	int hh = 300 + r_count * 15;
	if (hh > 640){ ww = 640; }
	this->resize(ww, hh);

	// > ��������
	this->local_dataList = p;
	this->local_class = c_f;
	this->isAddMode = false;
	this->putDataToUi();
}

/*-------------------------------------------------
		���� - ȡ������
*/
QList<QJsonObject> W_FastListWindow::getData(){
	return this->local_dataList;
};
/*-------------------------------------------------
		���� - �������� -> ui����
*/
void W_FastListWindow::putDataToUi() {
	//ֱ�ӿ���datalist
	this->refreshTable();
};
/*-------------------------------------------------
		���� - ui���� -> ��������
*/
void W_FastListWindow::putUiToData() {
	//ֱ�ӿ���datalist
};
/*-------------------------------------------------
		���� - �ύ���ݣ�У�飩
*/
void W_FastListWindow::acceptData(){
	this->putUiToData();

	emit acceptDataSignal(this->isAddMode, this->local_dataList);
	this->accept();
};