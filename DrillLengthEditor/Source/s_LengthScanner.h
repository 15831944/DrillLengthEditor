#pragma once

#include <QWidget>
#include "Utils/common/TTool.h"
#include "Utils/manager/txtRead/p_TxtFastReader.h"
#include "c_LEConfigData.h"

/*
-----==========================================================-----
		�ࣺ		�ı�ɨ����.h
		����ģ�飺	����ģ��
		���ܣ�		�ṩɨ�衢��дֱ�ӹ��ܡ�
					����ϸ��cpp��
-----==========================================================-----
*/
class S_LengthScanner : public QObject
{
	Q_OBJECT

	public:
		S_LengthScanner();
		~S_LengthScanner();
		static S_LengthScanner* cur_manager;			//����
		static S_LengthScanner* getInstance();			//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		void init();									//��ʼ��
		
	//-----------------------------------
	//----ɨ��
	public:
												//ɨ�� - ��ȡ���� + ���ֵ
		C_LEPlugin* doScanPlugin(QString file_name);
												//ɨ�� - ˢ�²������ֵ
		void refreshScanPluginLenth(C_LEPlugin* plugin);

												//ɨ�� - �ı��Ƿ����"xxx-10"���и�ʽ
		bool isPluginIncludedLengthParam(QString context);


	//-----------------------------------
	//----��д
	public:
												//��д - ���ֵ�޸ģ�ʧ�ܷ��ؿ��ַ�����
		QString doOverwritePlugin(QString context, C_LEPluginParam param, C_LEConfigData config);
	private:
												//��д - ���� "�׶�-1" ��ȡ�� "@param �׶�-1" ��ȫ�������ַ���
		QStringList getParamStringList(QStringList contextList, QString paramName);
		
};

