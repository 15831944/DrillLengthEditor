#pragma once

#include <QWidget>
#include <QSet>
#include "c_LEConfigData.h"

/*
-----==========================================================-----
		�ࣺ		���ֵ�༭ ���̹���.h
		����ģ�飺	����ģ��
		���ܣ�		���� ���� �� ui ���н顣
					�洢�ڲ����������ݣ�ui���������е����ݿ�����ʱˢ�¡�
					����ϸ��cpp��
-----==========================================================-----
*/
class S_LengthFlowManager : public QObject
{
	Q_OBJECT

	public:
		S_LengthFlowManager();
		~S_LengthFlowManager();
		static S_LengthFlowManager* cur_manager;			//����
		static S_LengthFlowManager* getInstance();			//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		void init();										//��ʼ��

	//-----------------------------------
	//----���ļ�
	private:
		C_LEPlugin* m_single_plugin;			//�����Ϣ��ֻ����
		QList<C_LEConfigData> m_single_data;	//���ò�������ʱ��
	public:
												//���ļ� - �򿪵��ļ������سɹ������
		bool openSingle(QString file_name);
												//���ļ� - ��ȡ�򿪺�Ĳ������
		C_LEPlugin* getLastSinglePlugin();
												//���ļ� - �༭���
		void editSingle();
												//���ļ� - ִ���޸�
		void executeSingle();


	//-----------------------------------
	//----�����ļ�
	private:
		QList<C_LEPlugin*> m_batch_pluginList;		//�����Ϣ��ֻ����
		QList<C_LEConfigData> m_batch_dataList;		//���ò�������ʱ��
		QList<C_LEConfigData> m_batch_storageList;	//���ò������洢��ֻ����������
	public:
												//�����ļ� - ���ļ���
		void openBatch(QString dir_name);
												//�����ļ� - ��ȡ�򿪺�Ĳ������
		QList<C_LEPlugin*> getLastBatchPlugin();
												//�����ļ� - �༭���
		void editBatchOne( C_LEPlugin* plugin );
												//�����ļ� - ִ���޸�
		void executeBatch();
	private:
												//�����ļ� - ��һ�����
		C_LEPlugin* openBatchOne(QString file_name);
		
	public:
												//�����ļ� - ��������
		void importConfig();
												//�����ļ� - ��������
		void exportConfig();

	private:
												//�����ļ� - �򿪴��ڱ༭���
		QJsonObject editOneWithWindow(C_LEPlugin* plugin, QList<C_LEConfigData> data);
												//�����ļ� - �������û�ȡ�����
		QList<C_LEConfigData> getBatchConfigDataByPlugin(C_LEPlugin* plugin);
												//�����ļ� - ˢ�±༭��Ϣ
		void refreshBatchEditMessage();
		
};

