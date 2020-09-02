#ifndef W_FastWindow_H
#define W_FastWindow_H

#include "ui_W_FastWindow.h"
#include "../fastForm/p_FastForm.h"

/*
-----==========================================================-----
		�ࣺ		���ٴ��� ����.h
		�汾��		v1.01
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		������д�������Ĵ��ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_FastWindow : public QDialog
{
	Q_OBJECT

	public:
		W_FastWindow(QWidget *parent = 0);
		~W_FastWindow();
		
	public:
										//�س�����
		void keyPressEvent(QKeyEvent *event);
		

	public:
		P_FastForm* m_fastForm;

	//-----------------------------------
	//----����
	public:
		bool isAddMode;
		C_FastClass local_class;
		QJsonObject local_data;
	public:
										//���� - �������ݣ���ӣ�
		void setDataInAddMode(C_FastClass c_f);
										//���� - �������ݣ��޸ģ�
		void setDataInModifyMode(C_FastClass c_f, QJsonObject p);
										//���� - ȡ������
		QJsonObject getData();
										//���� - �������� -> ui����
		void putDataToUi();							
										//���� - ui���� -> ��������
		void putUiToData();

	public slots:
										//���� - �ύ���ݣ�У�飩
		void acceptData();	
	signals:
		void acceptDataSignal(bool isAddMode, QJsonObject data);

	private:
		Ui::W_FastWindow ui;
	//-----------------------------------
};

#endif // W_FastWindow_H
