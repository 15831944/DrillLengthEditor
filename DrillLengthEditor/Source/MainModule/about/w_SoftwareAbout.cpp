#include "stdafx.h"
#include "W_SoftwareAbout.h"

#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		���ڴ���.cpp
		����ģ�飺	������ģ��
		���ܣ�		���ڴ��ڡ�

		ʹ�÷�����
				>�򿪴���
					W_SoftwareAbout d;
					d.exec();

-----==========================================================-----
*/
W_SoftwareAbout::W_SoftwareAbout(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton, &QToolButton::clicked, this, &W_SoftwareAbout::openUserManual);

	//-----------------------------------
	//----ui��ʼ��
	TTool::_chinese_(ui.buttonBox);

}

W_SoftwareAbout::~W_SoftwareAbout(){
}


/* --------------------------------------------------------------
		�ؼ� - �û��ֲ�
*/
void W_SoftwareAbout::openUserManual() {
	QString sPath = qApp->applicationDirPath();

	QFileInfo info("���ڲ�����ֵ�༭��.docx");
	if (!info.exists()){
		QMessageBox::warning(this, "����", "�ĵ������ˡ�", QMessageBox::Yes);
		return;
	}
	QDesktopServices::openUrl(QUrl("file:///" + info.absoluteFilePath()));

}