#ifndef W_TipWaitBox_H
#define W_TipWaitBox_H

#include "ui_w_TipWaitBox.h"

/*
-----==========================================================-----
		�ࣺ		�ް�ť�ȴ���ʾ����.h
		����ģ�飺	����ģ��
		���ܣ�		������ʾ�û����������
-----==========================================================-----
*/
class W_TipWaitBox : public QDialog
{
	Q_OBJECT

	public:
		W_TipWaitBox(QString context,QWidget *parent = 0);
		~W_TipWaitBox();


	public slots:
		void changeText(QString s);

	private:
		Ui::W_TipWaitBoxClass ui;

};

#endif // W_TipWaitBox_H
