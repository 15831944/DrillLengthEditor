#pragma once

#include <QObject>

/*
-----==========================================================-----
		�ࣺ		�ı����ٶ�ȡ��.h
		�汾��		v1.07
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		��ȡ �ı��ļ������ݣ�����������
					���ɶԶ�ƪ�ı��������ٶȿ죨���ȿ������ܣ���
					����ϸ��cpp��
-----==========================================================-----
*/

class P_TxtFastReader
{

	//-----------------------------------
	//----�����ṹ
	public:
		P_TxtFastReader(QString context);
		~P_TxtFastReader();
		
	//-----------------------------------
	//----����
	private:
		QStringList log_context_list;	//log���ַ��������ģ�
		
	//-----------------------------------
	//----ȫ��
	private:
		bool m_trim;
		QStringList m_replace_strFrom;
		QStringList m_replace_strTo;
		QList<QRegExp> m_replace_expFrom;
		QStringList m_replace_expTo;
	public:
										//ȫ�� - ����ո�Ԥ����
		void prepare_trimAllRows();
										//ȫ�� - �滻�ַ���Ԥ����
		void prepare_replaceInStrings(QString re_str, QString str);
		void prepare_replaceInStrings(QRegExp re, QString str);

	private:
										//ȫ�� - ִ��Ԥ������
		QString doPrepare(QString str);

	//-----------------------------------
	//----ֱ�Ӳ�����directly��
	public:
										//ֱ�� - ��i��
		QString d_rowAt(int i);
										//ֱ�� - ��ȡȫ������
		int d_rowCount();
										//ֱ�� - ��ȡ������
										//		������1���������������ַ���
										//		�����ء�������ֵ��δ�ҵ�����-1��
		int d_indexOf(QString contains);
		int d_indexOf(QRegExp re_contains);
										//ֱ�� - ��ȡ�����У���ĩβ�ң�
										//		������1���������������ַ���
										//		�����ء�������ֵ��δ�ҵ�����-1��
		int d_lastIndexOf(QString contains);
		int d_lastIndexOf(QRegExp re_contains);
										//ֱ�� - ��ȡ�����У�ָ����Χ��
										//		������1����ʼ��
										//		������2����ֹ��
										//		�����ء�����ֵ��δ�ҵ�����-1��
		int d_indexOf(QString contains, int n, int m = -1);
		int d_indexOf(QRegExp re_contains, int n, int m = -1);
										//ֱ�� - ��ȡ�������µ�������
										//		������1����ʼ��
										//		������2������
										//		�����ء����б�δ�ҵ�/��곬�������� ���ؿ��б�
		QStringList d_getRows(int n, int row_count = -1);
										//ֱ�� - ��ȡ������������
										//		������1�������������ַ���
										//		�����ء����а������У�δ�ҵ����ؿ��б�
		QList<int> d_getAllRowIndexsContains(QString contains);
		QList<int> d_getAllRowIndexsContains(QRegExp re_contains);
		QStringList d_getAllRowsContains(QString contains);
		QStringList d_getAllRowsContains(QRegExp re_contains);
		
		
	//-----------------------------------
	//----�ַ���
	public:
										//�ַ��� - ��ȡ����������եȡ�� 1.0e3 �����������пո�ű���ȡ��
										//		������1�������ַ���
										//		�����ء����б�
		QList<double> s_getDoubleInRow(QString row);
										//�ַ��� - ��ȡ��������եȡ�� 23 �����������пո�ű���ȡ��
										//		������1�������ַ���
										//		�����ء����б�
		QList<int> s_getIntInRow(QString row);

};

