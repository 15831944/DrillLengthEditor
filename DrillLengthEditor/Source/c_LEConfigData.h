#pragma once


/*
-----==========================================================-----
		�ࣺ		�������.h��ֻ����
		����ģ�飺	����ģ��
		���ܣ�		����Ĺ̶��������ݡ�

		˵����		������ʵֻ�漸����Ҫ�����ݡ�
					�����ṹ���ô� ʵ���� �������ݵĸ�����Ͻ����
					�����⣬�����ܱ�������Ψһ�ԣ�����"�׶�-%d"��"�׶�"���������������
-----==========================================================-----
*/
class C_LEPluginParam{
	public:
		C_LEPluginParam();
		~C_LEPluginParam();
	private:
		QString paramKey;				//������
		QString parentKey;				//�������
		QString var;					//������
		int varLen;						//�������ֵ
		int realLen;					//ʵ�����ֵ
	public:
										//���� - ��ʼ��
		void initParam(QString param, QString parentKey, QString var);
										//��ȡ - ������ "�׶�-%d"
		QString getParamKey();
										//��ȡ - ������� "--�׶���%d��%d--"
		QString getParentKey();
										//��ȡ - ������ "DrillUp.g_SSpE_list_length"
		QString getVarName();

										//���� - ���� �������ֵ
		void setVarLen(int len);
										//���� - ���� ʵ�����ֵ
		void setRealLen(int len);
										//��ȡ - �������ֵ
		int getVarLen();
										//��ȡ - ʵ�����ֵ
		int getRealLen();

										//��ȡ - ������ʾ�� "�׶�"
		QString getParamShowingName();
										//��ȡ - ������ "�׶�-210"����1��ʼ������
		QString getParamName(int index);
										//��ȡ - �������� "--�׶���21��40--"����1��ʼ������
		QString getParentName(int index);
										//��ȡ - �Ƿ����
		bool isParentGrouping();
};
/*
-----==========================================================-----
		�ࣺ		�����Ϣ.h��ֻ����
		����ģ�飺	����ģ��
		���ܣ�		����Ĺ̶���Ϣ���ݡ�
-----==========================================================-----
*/
class C_LEPlugin{
	public:
		C_LEPlugin();
		~C_LEPlugin();
	public:
		QString pluginName;					//�������Ӣ�ģ�
		QString pluginDesc;					//�����飨��������
		QString pluginAuthor;				//�������
		QList<C_LEPluginParam> paramList;	//�������
		bool paramForbidden;				//��ֹ�༭

		QString fullPath;					//����ļ�·��
		QString context;					//����ı�
		QString message;					//�����Ϣ����ȡ����ʾ���ַ�����
		QString editMessage;				//����޸���Ϣ���༭�󣬱༭���ݵ��ַ�����
	public:
											//���ݱ�������ȡ����
		C_LEPluginParam getParamByKey(QString paramKey);
											//�ж� - ���ж�
		bool isNull();
											//�ж� - �Ƿ񱻽���
		bool isForbidden();
											//�ж� - �Ƿ�ɱ༭
		bool isEditable();
											//�ж� - �����Լ��
		bool isIntegrity();
};


/*
-----==========================================================-----
		�ࣺ		���ò���.h���洢��
		����ģ�飺	����ģ��
		���ܣ�		��������ò������ݡ�
-----==========================================================-----
*/
class C_LEConfigData {
	public:
		C_LEConfigData();
		~C_LEConfigData();
	private:
		QString pluginName;			//�����
		QString paramKey;			//������
		int configLen;				//�������ֵ
	public:
											//���� - ��ʼ��
		void initParam(QString pluginName, QString paramKey, int realLen);
											//��ȡ - �������Ӣ�ģ�
		QString getPluginName();
											//��ȡ - ������ "�׶�-%d"
		QString getParamKey();
											//��ȡ - ������ʾ�� "�׶�"
		QString getParamShowingName();
											//��ȡ - �������ֵ
		int getConfigLen();

											//ʵ���� -> QJsonObject
		QJsonObject getJsonObject();
											//QJsonObject -> ʵ����
		void setJsonObject(QJsonObject obj);
											//���ж�
		bool isNull();
											//���������
		const bool operator== (const C_LEConfigData& a)const;
};
inline uint qHash(C_LEConfigData &key, uint seed){	//qHasgȫ������
	return qHash(key.getPluginName(), seed) * qHash(key.getParamKey(), seed);
};