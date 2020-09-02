#ifndef W_FastListWindow_H
#define W_FastListWindow_H

#include "ui_W_FastListWindow.h"
#include "../fastForm/p_FastForm.h"

/*
-----==========================================================-----
		�ࣺ		�����б� ����.h
		�汾��		v1.01
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���ݱ༭�Ŀ����б���ơ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_FastListWindow : public QDialog
{
	Q_OBJECT

	public:
		W_FastListWindow(QWidget *parent = 0);
		~W_FastListWindow();
		
	//-----------------------------------
	//----���
	public slots:
		void addOneRow();			//���
		void modifyOneRow();		//�༭
		void deleteOneRow();		//ɾ��

		void refreshTable();		//ˢ�±��

	//-----------------------------------
	//----����
	public:
		bool isAddMode;
		C_FastClass local_class;
		QList<QJsonObject> local_dataList;
	public:
										//���� - ��������
		void setData(C_FastClass c_f, QList<QJsonObject> p);
										//���� - ȡ������
		QList<QJsonObject> getData();
										//���� - �������� -> ui����
		void putDataToUi();							
										//���� - ui���� -> ��������
		void putUiToData();			

	public slots:
										//���� - �ύ���ݣ�У�飩
		void acceptData();	
	signals:
		void acceptDataSignal(bool isAddMode, QList<QJsonObject> data);

	private:
		Ui::W_FastListWindow ui;
	//-----------------------------------
};

#endif // W_FastListWindow_H
