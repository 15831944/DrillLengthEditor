#pragma once

#include <QWidget>

/*
-----==========================================================-----
		�ࣺ		�����ඨ��.h
		�汾��		v1.07
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		����һ������д�õ��ඨ�壬���ٱ������ٴ���ͨ�á�
					�����������ڶ���model�������ֶζ����ַ�����
					���������������������ġ�
					����ϸ��cpp��
-----==========================================================-----
*/
class C_FastClassParam;
class C_FastClass{

	public:
		C_FastClass();
		C_FastClass(QString className);
		~C_FastClass();
		
	//-----------------------------------
	//----����
	public:
							//���� - ����
		void setClassName(QString classNameChinese);
		void setClassNameEnglish(QString classNameEnglish);
		void setClassNameShowing(QString classNameShowing);
							//���� - double
		void addDouble(QString paramNameChinese);
		void addDouble(QString paramNameChinese, QString defaultValue);
							//���� - Int
		void addInt(QString paramNameChinese);
		void addInt(QString paramNameChinese, QString defaultValue);
							//���� - QString
		void addQString(QString paramNameChinese);
		void addQString(QString paramNameChinese, QString defaultValue);
							//���� - QString����ѡ�
		void addQStringWithChoose(QString paramNameChinese, QString defaultValue, QStringList chooseList);
							//�߼� - ��Ƕ��
		void addFastClassQWidget(C_FastClass fastClass);
		void addFastClassOneLine(C_FastClass fastClass);
		void addFastClassQGroupBox(C_FastClass fastClass);

	//-----------------------------------
	//----��ȡ
	public:
							//��ȡ - ����
		QString getClassNameChinese();
		QString getClassNameEnglish();
		QString getClassNameShowing();
							//��ȡ - �������������FastClass��
		QList<C_FastClassParam> getParamList();
							//��ȡ - �����������FastClassȫ����̯����
		QList<C_FastClassParam> getConvertedParamList();
							//��ȡ - ���в���������������������Ĳ�����
		QStringList getParamChineseNameList();
							//��ȡ - ���в���Ӣ����������������Ĳ�����
		QStringList getParamEnglishNameList();
							//��ȡ - �ӿ�����
		C_FastClass getChildClass(QString chineseName);
							//��ȡ - �жϿ�
		bool isNull();

	//-----------------------------------
	//----����
	public:
							//���� - Ӣ����
		void setParamEnglishName(QString paramNameChinese, QString paramNameEnglish);
							//���� - ��ʾ��
		void setParamShowingName(QString paramNameChinese, QString showingName);
							//���� - ������
		void setParamNotNull(QString paramNameChinese, bool notNull);
							//���� - ��׺
		void setParamSuffix(QString paramNameChinese, QString suffix);
		
	//-----------------------------------
	//----����
	public:
							//���� - SIд��
		void setParamSI(QString paramNameChinese, bool isSI);
							//���� - ���ɱ༭
		void setParamEditable(QString paramNameChinese, bool isEditable);
							//���� - Ĭ��ֵ�޸�
		void setParamDefaultValue(QString paramNameChinese, QString defaultValue);
		
	//-----------------------------------
	//----�߼�
	public:
							//�߼� - ��������
		void setParamColumn(QString paramNameChinese, int col);
		
		
	//-----------------------------------
	//----���⹦��
	public:
							//���⹦�� - ��QJsonObject�����ݣ����ݸ���ĸ�ʽ����䵽table�У����ģ�
		void fillDataInTableWidget(QTableWidget* tableWidget, QList<QJsonObject> data_list);
							//���⹦�� - ��QJsonObject�����ݣ����ݸ���ĸ�ʽ����䵽table�У�Ӣ�ģ�
		void fillDataInTableWidgetEnglish(QTableWidget* tableWidget, QList<QJsonObject> data_list);
							//���⹦�� - jsonobj Ӣ�� -> ����
		QJsonObject convertEnglishToChinese(QJsonObject data);
							//���⹦�� - jsonobj Ӣ�� -> ���ģ�ת���˵��ӵ���
		QJsonObject convertEnglishToChineseExcludely(QJsonObject data);
							//���⹦�� - jsonobj ���� -> Ӣ��
		QJsonObject convertChineseToEnglish(QJsonObject data);
							//���⹦�� - jsonobj ���� -> Ӣ�ģ�ת���˵��ӵ���
		QJsonObject convertChineseToEnglishExcludely(QJsonObject data);
							//���⹦�� - ȥ���������ı�ʶ��ʽ
		QString removeSpecialChineseCharacter(QString paramNameChinese);

	//-----------------------------------
	//----˽�в���
	protected:
		QString classNameChinese;			//��������
		QString classNameEnglish;			//��Ӣ����
		QString classNameShowing;			//����ʾ��
		QList<C_FastClassParam> paramList;	//�������
		QStringList nameChinese_list;		//ȫ��������
		QStringList nameEnglish_list;		//ȫ��Ӣ����
	protected:
		C_FastClassParam getParamByName(QString nameChinese);
		int getIndexByName(QString nameChinese);
		void checkDuplicatedChineseValue(QString nameChinese);
		void checkDuplicatedEnglishValue(QString nameEnglish);
};
/*
-----==========================================================-----
		�ࣺ		���������.h
-----==========================================================-----
*/
class C_FastClassParam{

	public:
		C_FastClassParam();
		~C_FastClassParam();

	public:
		QString nameChinese;		//������
		QString nameEnglish;		//Ӣ����
		QString type;				//����
		QString widgetType;			//������
		QString defaultValue;		//Ĭ��ֵ
		QStringList chooseList;		//ѡ���б�

		QString nameShowing;		//ʵ����ʾ��
		bool notNull;				//����
		QString suffix;				//��׺����λ��
		bool isSI;					//SIд��
		bool isEditable;			//�ɱ༭

		int columnPos;				//������
		C_FastClass fastClass;		//Ƕ����

		QString tempA;				//��������A
		QString tempB;				//��������B
		QString tempC;				//��������C
		QString tempD;				//��������D
		QString tempE;				//��������E
		QString tempF;				//��������F

	//-----------------------------------
	//----��ȡ
	public:
									//���������
		const bool operator== (const C_FastClassParam& a)const;
									//�жϿ�
		bool isNull();
									//��ȡ - ��ʾ�ı���
		QString getShowingName();
	public:
									//��ȡ - ȥ���������ı�ʶ���ַ�����̬������
		static QString removeSpecialChineseCharacter(QString nameChinese);

};