#include "stdafx.h"

#include "c_LEConfigData.h"
#include "Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		�������.cpp��ֻ����
-----==========================================================-----
*/
C_LEPluginParam::C_LEPluginParam(){
	this->paramKey = "";
	this->parentKey = "";
	this->var = "";
	this->varLen = 0;
	this->realLen = 0;
}
C_LEPluginParam::~C_LEPluginParam(){
}

/*-------------------------------------------------
		���� - ��ʼ��
*/
void C_LEPluginParam::initParam(QString param, QString parentKey, QString var){
	this->paramKey = param;
	this->parentKey = parentKey;
	this->var = var;
}
/*-------------------------------------------------
		��ȡ - ������
*/
QString C_LEPluginParam::getParamKey(){
	return this->paramKey;
}
/*-------------------------------------------------
		��ȡ - �������
*/
QString C_LEPluginParam::getParentKey(){
	return this->parentKey;
}
/*-------------------------------------------------
		��ȡ - ������
*/
QString C_LEPluginParam::getVarName(){
	return this->var;
}
/*-------------------------------------------------
		��ȡ - �������ֵ
*/
void C_LEPluginParam::setVarLen(int len){
	this->varLen = len;
}
int C_LEPluginParam::getVarLen(){
	return varLen;
}
/*-------------------------------------------------
		��ȡ - ʵ�����ֵ
*/
void C_LEPluginParam::setRealLen(int len){
	this->realLen = len;
}
int C_LEPluginParam::getRealLen(){
	return realLen;
}
/*-------------------------------------------------
		��ȡ - ������ʾ��
*/
QString C_LEPluginParam::getParamShowingName(){
	return this->paramKey.split("-").at(0);
}
/*-------------------------------------------------
		��ȡ - ����������1��ʼ������
*/
QString C_LEPluginParam::getParamName(int index){
	QString i_str = QString::number(index);
	QString result = this->paramKey;
	result = result.replace("%d", i_str);
	return result;
}
/*-------------------------------------------------
		��ȡ - ������������1��ʼ������
*/
QString C_LEPluginParam::getParentName(int index){
	if (this->isParentGrouping() == false){ return ""; }
	
	index--;
	int i = floor(index / 20);
	int start = 20 * i + 1;
	int end = 20 * (i + 1);
	QString str_start = QString::number(start);
	if (start == 1){ str_start = " 1"; };
	QString result = this->getParentKey();
	result.replace(result.lastIndexOf("%d"), 2, QString::number(end));
	result.replace("%d", str_start);

	return result;
}
/*-------------------------------------------------
		��ȡ - �Ƿ����
*/
bool C_LEPluginParam::isParentGrouping(){
	return this->parentKey.contains("%d");
}

/*
-----==========================================================-----
		�ࣺ		�����Ϣ.cpp��ֻ����
-----==========================================================-----
*/
C_LEPlugin::C_LEPlugin(){
	this->pluginName = "";
	this->pluginDesc = "";
	this->pluginAuthor = "";
	this->paramList = QList<C_LEPluginParam>();
	this->paramForbidden = false;
	this->context = "";
	this->message = "";
	this->editMessage = "";
}
C_LEPlugin::~C_LEPlugin(){
}
C_LEPluginParam C_LEPlugin::getParamByKey(QString paramKey){
	for (int i = 0; i < this->paramList.count(); i++){
		C_LEPluginParam p = this->paramList.at(i);
		if (p.getParamKey() == paramKey){
			return p;
		}
	}
	return C_LEPluginParam();
}
/*-------------------------------------------------
		�ж� - ���ж�
*/
bool C_LEPlugin::isNull(){
	return this->pluginName == "" || this->pluginDesc == "";
}
/*-------------------------------------------------
		�ж� - �Ƿ񱻽���
*/
bool C_LEPlugin::isForbidden(){
	return this->paramForbidden;
}
/*-------------------------------------------------
		�ж� - �Ƿ�ɱ༭
*/
bool C_LEPlugin::isEditable(){
	if (this->paramList.count() == 0){ return false; }
	return true;
}
/*-------------------------------------------------
		�ж� - �����Լ��
*/
bool C_LEPlugin::isIntegrity(){
	for (int i = 0; i < this->paramList.count(); i++){
		C_LEPluginParam pluginParam = this->paramList.at(i);

		if (pluginParam.getRealLen() == 0){ return false; }
		if (pluginParam.getVarName() == "null"){ continue; }
		if (pluginParam.getVarLen() == 0){ return false; }

		// > �Ա�
		if (pluginParam.getRealLen() != pluginParam.getVarLen()){
			return false;
		}
	}
	return true;
}


/*
-----==========================================================-----
		�ࣺ		���ò���.cpp���洢��
-----==========================================================-----
*/
C_LEConfigData::C_LEConfigData(){
	this->pluginName = "";
	this->paramKey = "";
	this->configLen = -1;
}
C_LEConfigData::~C_LEConfigData(){
}

/*-------------------------------------------------
		���� - ��ʼ��
*/
void C_LEConfigData::initParam(QString pluginName, QString paramKey, int realLen){
	this->pluginName = pluginName;
	this->paramKey = paramKey;
	this->configLen = realLen;
}
/*-------------------------------------------------
		��ȡ - �������Ӣ�ģ�
*/
QString C_LEConfigData::getPluginName(){
	return this->pluginName;
}
/*-------------------------------------------------
		��ȡ - ������ "�׶�-%d"
*/
QString C_LEConfigData::getParamKey(){
	return this->paramKey;
}
/*-------------------------------------------------
		��ȡ - ������ʾ�� "�׶�"
*/
QString C_LEConfigData::getParamShowingName(){
	return this->paramKey.split("-").at(0);
}
/*-------------------------------------------------
		��ȡ - �������ֵ
*/
int C_LEConfigData::getConfigLen(){
	return this->configLen;
}
/*-------------------------------------------------
		ʵ���� -> QJsonObject
*/
QJsonObject C_LEConfigData::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("pluginName", this->pluginName);
	obj.insert("paramKey", this->paramKey);
	obj.insert("realLen", this->configLen);

	return obj;
}
/*-------------------------------------------------
		QJsonObject -> ʵ����
*/
void C_LEConfigData::setJsonObject(QJsonObject obj){
	this->pluginName = obj.value("pluginName").toString();
	this->paramKey = obj.value("paramKey").toString();
	this->configLen = obj.value("realLen").toInt();
}
/*-------------------------------------------------
		���ж�
*/
bool C_LEConfigData::isNull(){
	return this->paramKey == "" || this->pluginName == "";
}
/*-------------------------------------------------
		���������
*/
const bool C_LEConfigData::operator== (const C_LEConfigData& a)const {
	return this->pluginName == a.pluginName && this->paramKey == a.paramKey;
}