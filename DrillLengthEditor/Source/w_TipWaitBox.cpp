#include "stdafx.h"

#include "w_TipWaitBox.h"
#include <QtWidgets>

/*
-----==========================================================-----
		�ࣺ		�ް�ť�ȴ���ʾ����.cpp
		����ģ�飺	����ģ��
		���ܣ�		������ʾ�û����������
-----==========================================================-----
*/
W_TipWaitBox::W_TipWaitBox(QString context,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(context);
	ui.label->setText(context);
	ui.label->repaint();
}

W_TipWaitBox::~W_TipWaitBox()
{

}


void W_TipWaitBox::changeText(QString s) {
	ui.label->setText(s);
	ui.label->repaint();
}


