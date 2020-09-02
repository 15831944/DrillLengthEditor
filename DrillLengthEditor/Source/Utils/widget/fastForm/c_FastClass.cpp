#include "stdafx.h"

#include "c_FastClass.h"
#include "../../common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		�����ඨ��.cpp
		�汾��		v1.07
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		����һ������д�õ��ඨ�壬���ٱ������ٴ���ͨ�á�
					�����������ڶ���model�������ֶζ����ַ�����
					���������������������ġ�
					
		���ܣ�		1.���ã�	������Double��Int��QString��QString��������
					2.���裺	Ӣ��������ʾ�����������׺
					3.���裺	SIд�������ɱ༭��Ĭ��ֵ�޸�
					4.�߼���	������������Ƕ��
					���⣺		QJsonObject��䵽table�С�QJsonObject��Ӣ��ת��

		����Լ����	1.��������Ӣ���������ظ�����������ظ���������������������
					2.Ƕ���� ��������Ҫ��һ����������Ȼ������鱨��

		�Զ�����	1.���Ĳ�����ֵȫ��ΪQString��
					  Ӣ�Ĳ�������������Զ�תdouble��int��
					2.��׺Ϊ"Hz"ʱ���Զ�SIд����
					3.����Ϊdoubleʱ����ʾtablewidgetʱ�Զ���Ӻ�׺��
					4.��ʶ��ʽ��"<-��ʶ�ַ�->������"��
					  ���Ĳ������иø�ʽ���ַ������ᱻ��ʾ��������Ҳ������showingName���ã�
					
		ʹ�÷�����
				>����
					c_class = C_FastClass("Ŀ��ģ��");						//�����൱��ֱ����дһ�Ѳ������������ڿ��ٱ������ٴ���
					c_class.addDouble				("λ��", "0.0");		//��ϸ�� ���ٱ������ٴ��� ��ʹ�÷���
					c_class.addDouble				("����", "0.0"); 
					c_class.addQString				("˵��", "0.0");
					c_class.addQString				("����", "0.0");
				>�����޸�
					c_class.addQString				("������", "0");		//������Ĳ����󣬿���������Ӹ�������
					c_class.setParamEnglishName		("������", "ModPulMaxInterfPulseWidth");
					c_class.setParamShowingName		("������", "������������");
					c_class.setParamSuffix			("������", "��s");
				>��Ƕ��
					c_class = C_FastClass("����");							//Ƕ�׺�����Ȼ��Ҫȷ�����Ĳ��������ظ�
						C_FastClass class_6 = C_FastClass("�źŷ�Χ");
						class_6.addQString						("�ź�����", "0");
						class_6.setParamEnglishName				("�ź�����", "ModPulSignalCarrierFreqStart");
						class_6.setParamSuffix					("�ź�����", "");
						class_6.addQString						("�ź�����", "0");
						class_6.setParamEnglishName				("�ź�����", "ModPulSignalCarrierFreqEnd");
						class_6.setParamSuffix					("�ź�����", "Hz");
					c_class.addFastClassOneLine				(class_6);
				>����
					this->m_target_class.addQString("<-SPAN->xxxxx", "");	//����ָ��ǰ׺�ı����������Ϊ������Ŀ�ռλ����

-----==========================================================-----
*/
C_FastClass::C_FastClass(){
	this->classNameChinese = "";
	this->classNameEnglish = "";
	this->paramList = QList<C_FastClassParam>();
	this->nameChinese_list = QStringList() << this->classNameChinese;
	this->nameEnglish_list = QStringList() << this->classNameEnglish;
}
C_FastClass::C_FastClass(QString className)
{
	this->classNameChinese = className;
	this->classNameEnglish = "";
	this->paramList = QList<C_FastClassParam>();
	this->nameChinese_list = QStringList() << this->classNameChinese;
	this->nameEnglish_list = QStringList() << this->classNameEnglish;
}

C_FastClass::~C_FastClass(){
}

/*-------------------------------------------------
		˽�� - ����������ȡ����
*/
C_FastClassParam C_FastClass::getParamByName(QString nameChinese){
	for (int i = 0; i < this->paramList.count(); i++){
		C_FastClassParam c_fp = this->paramList.at(i);
		if (c_fp.nameChinese == nameChinese){
			return c_fp;
		}
	}
	return C_FastClassParam();
}
int C_FastClass::getIndexByName(QString nameChinese){
	for (int i = 0; i < this->paramList.count(); i++){
		C_FastClassParam c_fp = this->paramList.at(i);
		if (c_fp.nameChinese == nameChinese){
			return i;
		}
	}
	return -1;
}

/*-------------------------------------------------
		˽�� - �ж�����
*/
void C_FastClass::checkDuplicatedChineseValue(QString nameChinese){
	if (nameChinese == ""){ return; }
	#ifdef DEBUG_OPEN_PRO
		if (nameChinese_list.indexOf(nameChinese) != -1){
			qDebug() << "[" + this->classNameChinese + "]�����������Ĳ�����" + nameChinese;
			Q_ASSERT(false);
		}
	#else
	
	#endif
	nameChinese_list.push_back(nameChinese);
}
void C_FastClass::checkDuplicatedEnglishValue(QString nameEnglish){
	if (nameEnglish == ""){ return; }
	#ifdef DEBUG_OPEN_PRO
		if (nameEnglish_list.indexOf(nameEnglish) != -1){
			qDebug() << "[" + this->classNameChinese + "]��������Ӣ�Ĳ�����" + nameEnglish;
			Q_ASSERT(false);
		}
	#else
	
	#endif
	nameEnglish_list.push_back(nameEnglish);
}

/*-------------------------------------------------
		���� - ����
*/
void C_FastClass::setClassName(QString className){
	this->nameChinese_list.removeOne(this->classNameChinese);
	this->classNameChinese = className;
	this->checkDuplicatedChineseValue(className);
}
void C_FastClass::setClassNameEnglish(QString className){
	this->nameEnglish_list.removeOne(this->classNameEnglish);
	this->classNameEnglish = className;
	this->checkDuplicatedEnglishValue(className);
}
void C_FastClass::setClassNameShowing(QString className){
	this->classNameShowing = className;
}
/*-------------------------------------------------
		���� - double
*/
void C_FastClass::addDouble(QString paramName){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = paramName;
	c_f.type = "Double";
	c_f.widgetType = "QLineEdit";
	this->checkDuplicatedChineseValue(paramName);
	this->paramList.push_back(c_f);
}
void C_FastClass::addDouble(QString paramName, QString defaultValue){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = paramName;
	c_f.type = "Double";
	c_f.widgetType = "QLineEdit";
	c_f.defaultValue = defaultValue;
	this->checkDuplicatedChineseValue(paramName);
	this->paramList.push_back(c_f);
}
/*-------------------------------------------------
		���� - Int
*/
void C_FastClass::addInt(QString paramName){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = paramName;
	c_f.type = "Int";
	c_f.widgetType = "QLineEdit";
	this->checkDuplicatedChineseValue(paramName);
	this->paramList.push_back(c_f);
}
void C_FastClass::addInt(QString paramName, QString defaultValue){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = paramName;
	c_f.type = "Int";
	c_f.widgetType = "QLineEdit";
	c_f.defaultValue = defaultValue;
	this->checkDuplicatedChineseValue(paramName);
	this->paramList.push_back(c_f);
}
/*-------------------------------------------------
		���� - QString
*/
void C_FastClass::addQString(QString paramName){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = paramName;
	c_f.type = "QString";
	c_f.widgetType = "QLineEdit";
	this->checkDuplicatedChineseValue(paramName);
	this->paramList.push_back(c_f);
}
void C_FastClass::addQString(QString paramName, QString defaultValue){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = paramName;
	c_f.type = "QString";
	c_f.widgetType = "QLineEdit";
	c_f.defaultValue = defaultValue;
	this->checkDuplicatedChineseValue(paramName);
	this->paramList.push_back(c_f);
}
/*-------------------------------------------------
		���� - QString����ѡ�
*/
void C_FastClass::addQStringWithChoose(QString paramName, QString defaultValue, QStringList chooseList){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = paramName;
	c_f.type = "QString";
	c_f.widgetType = "QComboBox";
	c_f.chooseList = chooseList;
	c_f.defaultValue = defaultValue;
	this->checkDuplicatedChineseValue(paramName);
	this->paramList.push_back(c_f);
}

/*-------------------------------------------------
		�߼� - ������Ƕ��
*/
void C_FastClass::addFastClassQWidget(C_FastClass fastClass){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = fastClass.getClassNameChinese();
	c_f.nameEnglish = fastClass.getClassNameEnglish();
	c_f.type = "FastClass";
	c_f.widgetType = "QWidget";
	c_f.fastClass = fastClass;

	// > ������������
	QStringList name_list = fastClass.getParamChineseNameList();
	Q_ASSERT(name_list.count() > 0);
	for (int i = 0; i < name_list.count(); i++){
		this->checkDuplicatedChineseValue(name_list.at(i));
	}
	QStringList eng_name_list = fastClass.getParamEnglishNameList();
	for (int i = 0; i < eng_name_list.count(); i++){
		this->checkDuplicatedEnglishValue(eng_name_list.at(i));
	}

	this->paramList.push_back(c_f);
}
void C_FastClass::addFastClassOneLine(C_FastClass fastClass){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = fastClass.getClassNameChinese();
	c_f.nameEnglish = fastClass.getClassNameEnglish();
	c_f.type = "FastClass";
	c_f.widgetType = "OneLine";
	c_f.fastClass = fastClass;

	// > ������������
	QStringList name_list = fastClass.getParamChineseNameList();
	Q_ASSERT(name_list.count() > 0);
	for (int i = 0; i < name_list.count(); i++){
		this->checkDuplicatedChineseValue(name_list.at(i));
	}
	QStringList eng_name_list = fastClass.getParamEnglishNameList();
	for (int i = 0; i < eng_name_list.count(); i++){
		this->checkDuplicatedEnglishValue(eng_name_list.at(i));
	}

	this->paramList.push_back(c_f);
}
void C_FastClass::addFastClassQGroupBox(C_FastClass fastClass){
	C_FastClassParam c_f = C_FastClassParam();
	c_f.nameChinese = fastClass.getClassNameChinese();
	c_f.nameEnglish = fastClass.getClassNameEnglish();
	c_f.type = "FastClass";
	c_f.widgetType = "QGroupBox";
	c_f.fastClass = fastClass;

	// > ������������
	QStringList name_list = fastClass.getParamChineseNameList();
	Q_ASSERT(name_list.count() > 0);
	for (int i = 0; i < name_list.count(); i++){
		this->checkDuplicatedChineseValue(name_list.at(i));
	}
	QStringList eng_name_list = fastClass.getParamEnglishNameList();
	for (int i = 0; i < eng_name_list.count(); i++){
		this->checkDuplicatedEnglishValue(eng_name_list.at(i));
	}

	this->paramList.push_back(c_f);
}

/*-------------------------------------------------
		���� - Ӣ����
*/
void C_FastClass::setParamEnglishName(QString paramNameChinese, QString paramNameEnglish){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	c_fp.nameEnglish = paramNameEnglish;
	this->checkDuplicatedEnglishValue(paramNameEnglish);		//���Ӣ�����ظ�
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}
/*-------------------------------------------------
		���� - ��ʾ��
*/
void C_FastClass::setParamShowingName(QString paramNameChinese, QString showingName){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	c_fp.nameShowing = showingName;
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}
/*-------------------------------------------------
		���� - ������
*/
void C_FastClass::setParamNotNull(QString paramNameChinese, bool notNull){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	c_fp.notNull = notNull;
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}
/*-------------------------------------------------
		���� - ��׺
*/
void C_FastClass::setParamSuffix(QString paramNameChinese, QString suffix){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	c_fp.suffix = suffix;
	if (suffix == "Hz"){ c_fp.isSI = true; }	//�Զ���Ϊsiд��
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}
/*-------------------------------------------------
		���� - SIд��
*/
void C_FastClass::setParamSI(QString paramNameChinese, bool isSI){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	if (c_fp.isNull()){ return; }
	c_fp.isSI = isSI;
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}
/*-------------------------------------------------
		���� - SIд��
*/
void C_FastClass::setParamEditable(QString paramNameChinese, bool isEditable){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	if (c_fp.isNull()){ return; }
	c_fp.isEditable = isEditable;
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}
/*-------------------------------------------------
		���� - Ĭ��ֵ�޸�
*/
void C_FastClass::setParamDefaultValue(QString paramNameChinese, QString defaultValue){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	if (c_fp.isNull()){ return; }
	c_fp.defaultValue = defaultValue;
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}

/*-------------------------------------------------
		�߼� - ��������
*/
void C_FastClass::setParamColumn(QString paramNameChinese, int col){
	C_FastClassParam c_fp = this->getParamByName(paramNameChinese);
	c_fp.columnPos = col;
	this->paramList.replace(this->getIndexByName(paramNameChinese), c_fp);
}

/*-------------------------------------------------
		��ȡ - ����
*/
QString C_FastClass::getClassNameChinese(){
	return classNameChinese;
}
QString C_FastClass::getClassNameEnglish(){
	return classNameEnglish;
}
QString C_FastClass::getClassNameShowing(){
	if (this->classNameShowing != ""){ return classNameShowing; }
	return this->classNameChinese.replace(QRegExp("<-[^>]*->"), "");
}
/*-------------------------------------------------
		��ȡ - ȫ��������/Ӣ����
*/
QStringList C_FastClass::getParamChineseNameList(){
	return nameChinese_list;
}
QStringList C_FastClass::getParamEnglishNameList(){
	return nameEnglish_list;
}
/*-------------------------------------------------
		��ȡ - �������������FastClass��
*/
QList<C_FastClassParam> C_FastClass::getParamList(){
	return paramList;
}
/*-------------------------------------------------
		��ȡ - �����������FastClassȫ����̯����
*/
QList<C_FastClassParam> C_FastClass::getConvertedParamList(){
	QList<C_FastClassParam> result_list = QList<C_FastClassParam>();
	for (int i = 0; i < this->paramList.count(); i++){
		C_FastClassParam c_fp = this->paramList.at(i);
		if (c_fp.type == "FastClass"){
			result_list.append(c_fp.fastClass.getConvertedParamList());
		}else{
			result_list.push_back(c_fp);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		��ȡ - �ӿ�����
*/
C_FastClass C_FastClass::getChildClass(QString chineseName){
	C_FastClassParam c_fp = this->getParamByName(chineseName);
	if (c_fp.type == "FastClass"){
		return c_fp.fastClass;
	}
	return C_FastClass();
}
/*-------------------------------------------------
		��ȡ - �жϿ�
*/
bool C_FastClass::isNull(){
	if (this->classNameChinese == ""){ return true; }
	return false;
}

/*-------------------------------------------------
		���⹦�� - ��QJsonObject�����ݣ����ݸ���ĸ�ʽ����䵽table��
*/
void C_FastClass::fillDataInTableWidget(QTableWidget* tableWidget, QList<QJsonObject> data_list){
	QList<C_FastClassParam> temp_cols = this->getConvertedParamList();
	QList<QJsonObject> temp_rows = data_list;
	tableWidget->setColumnCount(temp_cols.size());
	tableWidget->setRowCount(temp_rows.size());

	// > ��ͷ
	QStringList col_names = QStringList();
	for (int i = 0; i < temp_cols.size(); i++) {
		C_FastClassParam c_fp = temp_cols.at(i);
		col_names.append(c_fp.getShowingName());
	}
	tableWidget->setHorizontalHeaderLabels(col_names);

	// > ������
	for (int i = 0; i < temp_rows.size(); i++) {
		QJsonObject obj = temp_rows.at(i);
		for (int j = 0; j < temp_cols.size(); j++) {
			C_FastClassParam c_fp = temp_cols.at(j);
			QString data = "";		// > ���Ĳ�����ֱ����ʾ 
			data = obj.value(c_fp.nameChinese).toString();
			if (c_fp.isSI){			// > SIת��
				data = TTool::_to_QString_bySI_(data);
			}
			if (c_fp.type == "Double"){	// > double�Զ�����׺����λ��
				data += c_fp.suffix;
			}
			tableWidget->setItem(i, j, new QTableWidgetItem(data));
		}
	}
}
/*-------------------------------------------------
		���⹦�� - ��QJsonObject�����ݣ����ݸ���ĸ�ʽ����䵽table��
*/
void C_FastClass::fillDataInTableWidgetEnglish(QTableWidget* tableWidget, QList<QJsonObject> data_list){
	QList<C_FastClassParam> temp_cols = this->getConvertedParamList();
	QList<QJsonObject> temp_rows = data_list;
	tableWidget->setColumnCount(temp_cols.size());
	tableWidget->setRowCount(temp_rows.size());

	// > ��ͷ
	QStringList col_names = QStringList();
	for (int i = 0; i < temp_cols.size(); i++) {
		C_FastClassParam c_fp = temp_cols.at(i);
		col_names.append(c_fp.getShowingName());
	}
	tableWidget->setHorizontalHeaderLabels(col_names);

	// > ������
	for (int i = 0; i < temp_rows.size(); i++) {
		QJsonObject obj = temp_rows.at(i);
		for (int j = 0; j < temp_cols.size(); j++) {
			C_FastClassParam c_fp = temp_cols.at(j);
			QString data = "";		// > Ӣ�Ĳ�����double -> QString ��ʾ 
			if (obj.value(c_fp.nameEnglish).isDouble()){
				data =  QString::number(obj.value(c_fp.nameEnglish).toDouble());
			}else{
				data = obj.value(c_fp.nameEnglish).toString();
			}
			if (c_fp.isSI){			// > SIת��
				data = TTool::_to_QString_bySI_(data);
			}
			if (c_fp.type == "Double"){	// > double�Զ�����׺����λ��
				data += c_fp.suffix;
			}
			tableWidget->setItem(i, j, new QTableWidgetItem(data));
		}
	}
}
/*-------------------------------------------------
		���⹦�� - jsonobj Ӣ�� -> ����
*/
QJsonObject C_FastClass::convertEnglishToChinese(QJsonObject data){
	QList<C_FastClassParam> param_list = this->getConvertedParamList();
	QJsonObject result_obj = QJsonObject();
	QStringList keys = data.keys();
	for (int i = 0; i < keys.length(); i++){
		QString key = keys.at(i);
		QJsonValue value = data.value(key);

		bool inserted = false;
		for (int j = 0; j < param_list.length(); j++){
			C_FastClassParam c_p = param_list.at(j);
			if (c_p.nameEnglish == key){

				// > ���Ĳ�����double -> QString������ȫ��QString�� 
				if (value.isDouble()){
					result_obj.insert(c_p.nameChinese, QString::number(value.toDouble()));
				}
				else{
					result_obj.insert(c_p.nameChinese, value);
				}
				inserted = true;
			}
		}
		if (inserted == false){
			result_obj.insert(key, value);
		}
	}
	return result_obj;
}
/*-------------------------------------------------
		���⹦�� - jsonobj Ӣ�� -> ���ģ�ת���˵��ӵ���
*/
QJsonObject C_FastClass::convertEnglishToChineseExcludely(QJsonObject data){
	QList<C_FastClassParam> param_list = this->getConvertedParamList();
	QJsonObject result_obj = QJsonObject();
	QStringList keys = data.keys();
	for (int i = 0; i < keys.length(); i++){
		QString key = keys.at(i);
		QJsonValue value = data.value(key);

		for (int j = 0; j < param_list.length(); j++){
			C_FastClassParam c_p = param_list.at(j);
			if (c_p.nameEnglish == key){

				// > ���Ĳ�����double -> QString������ȫ��QString�� 
				if (value.isDouble()){
					result_obj.insert(c_p.nameChinese, QString::number(value.toDouble()));
				}
				else{
					result_obj.insert(c_p.nameChinese, value);
				}
			}
		}
	}
	return result_obj;
}
/*-------------------------------------------------
		���⹦�� - jsonobj ���� -> Ӣ��
*/
QJsonObject C_FastClass::convertChineseToEnglish(QJsonObject data){
	QList<C_FastClassParam> param_list = this->getConvertedParamList();
	QJsonObject result_obj = QJsonObject();
	QStringList keys = data.keys();
	for (int i = 0; i < keys.length(); i++){
		QString key = keys.at(i);
		QJsonValue value = data.value(key);
		if (key.contains("<-SPAN->")){ continue; }		//��ռλ������

		bool inserted = false;
		for (int j = 0; j < param_list.length(); j++){
			C_FastClassParam c_p = param_list.at(j);
			if (c_p.nameChinese == key){

				// > Ӣ�Ĳ����� QString -> double
				if (value.isString() && c_p.type == "Double"){
					result_obj.insert(c_p.nameEnglish, value.toString().toDouble());
				}
				else if (value.isString() && c_p.type == "Int"){
					result_obj.insert(c_p.nameEnglish, value.toString().toInt());
				}
				else{
					result_obj.insert(c_p.nameEnglish, value);
				}
				inserted = true;
			}
		}
		if (inserted == false){
			result_obj.insert(key, value);
		}
	}
	return result_obj;
}
/*-------------------------------------------------
		���⹦�� - jsonobj ���� -> Ӣ�ģ�ת���˵��ӵ���
*/
QJsonObject C_FastClass::convertChineseToEnglishExcludely(QJsonObject data){
	QList<C_FastClassParam> param_list = this->getConvertedParamList();
	QJsonObject result_obj = QJsonObject();
	QStringList keys = data.keys();
	for (int i = 0; i < keys.length(); i++){
		QString key = keys.at(i);
		QJsonValue value = data.value(key);
		if (key.contains("<-SPAN->")){ continue; }		//��ռλ������

		for (int j = 0; j < param_list.length(); j++){
			C_FastClassParam c_p = param_list.at(j);
			if (c_p.nameChinese == key){

				// > Ӣ�Ĳ����� QString -> double
				if (value.isString() && c_p.type == "Double"){
					result_obj.insert(c_p.nameEnglish, value.toString().toDouble());
				}
				else if (value.isString() && c_p.type == "Int"){
					result_obj.insert(c_p.nameEnglish, value.toString().toInt());
				}
				else{
					result_obj.insert(c_p.nameEnglish, value);
				}
			}
		}
	}
	return result_obj;
}



/*
-----==========================================================-----
		�ࣺ		���������.h
-----==========================================================-----
*/
C_FastClassParam::C_FastClassParam()
{
	this->nameChinese = "";
	this->nameEnglish = "";
	this->type = "";
	this->widgetType = "";
	this->defaultValue = "";
	this->chooseList = QStringList();

	this->notNull = false;
	this->suffix = "";
	this->isSI = false;
	this->isEditable = true;
	//this->fastClass;

	this->columnPos = 0;
	this->nameShowing = "";

	this->tempA = "";
	this->tempB = "";
	this->tempC = "";
	this->tempD = "";
	this->tempE = "";
	this->tempF = "";
}
C_FastClassParam::~C_FastClassParam(){
}

/*-------------------------------------------------
		���������
*/
const bool C_FastClassParam::operator== (const C_FastClassParam& a)const {
	return this->nameChinese == a.nameChinese;
}
/*-------------------------------------------------
		�жϿ�
*/
bool C_FastClassParam::isNull(){
	if (this->nameChinese == ""){ return true; }
	if (this->type == ""){ return true; }
	return false;
}
/*-------------------------------------------------
		��ȡ - ��ʾ�ı���
*/
QString C_FastClassParam::getShowingName(){
	if (this->nameShowing != ""){ return nameShowing; }
	return removeSpecialChineseCharacter(this->nameChinese);
}
/*-------------------------------------------------
		��ȡ - ȥ���������ı�ʶ���ַ�
*/
QString C_FastClassParam::removeSpecialChineseCharacter(QString nameChinese){
	return nameChinese.replace(QRegExp("<-[^>]*->"), "");
}