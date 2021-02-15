#include "stdafx.h"
#include "S_LengthFlowManager.h"

#include "Source/PluginModule/lengthEditor/s_LEAnnotationReader.h"
#include "Source/PluginModule/lengthEditor/s_LEConfigWriter.h"
#include "W_TipWaitBox.h"

#include "Source/Utils/widget/fastForm/c_FastClass.h"
#include "Source/Utils/widget/fastWindow/w_FastWindow.h"


/*
-----==========================================================-----
		�ࣺ		���ֵ�༭ ���̹���.h
		����ģ�飺	����ģ��
		���ܣ�		���� ���� �� ui ���н顣
					�洢�ڲ����������ݣ�ui���������е����ݿ�����ʱˢ�¡�

		Ŀ�꣺		���ļ���������
						> ���ļ�
						> �༭�ļ�
						> ִ���ļ�����

					�����ļ���������
						> ���ļ���
						> �༭�ļ�
						> ���뵼������
						> ִ�������ļ�����
		
		˵����		������������д��ͬһ�����У�����������Щ�ۻ���
					�����ԵĶ������ǳ��ƣ���Ҫ��������
					������Ҫ����һ��������Ĵ��ݡ���debug�ϵ�鿴��

-----==========================================================-----
*/

S_LengthFlowManager::S_LengthFlowManager(){
	init();
}
S_LengthFlowManager::~S_LengthFlowManager() {
}
/*  - - ���� - - */
S_LengthFlowManager* S_LengthFlowManager::cur_manager = NULL;
S_LengthFlowManager* S_LengthFlowManager::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_LengthFlowManager();
	}
	return cur_manager;
}
/*  - - ��ʼ�� - - */
void S_LengthFlowManager::init() {

}


/*-------------------------------------------------
		���ļ� - ��
*/
bool S_LengthFlowManager::openSingle(QString file_name){
	
	this->m_single_plugin = S_LEAnnotationReader::getInstance()->readPlugin(QFileInfo(file_name));

	// > ������
	QStringList temp_list = QStringList();
	if (m_single_plugin->isForbidden() == true){
		temp_list.push_back("�ò����ֹ�༭���ֵ��");
		this->m_single_plugin->message = temp_list.join("\n");
		return false;
	}
	if (m_single_plugin->isEditable() == false){
		temp_list.push_back("δ�ҵ��ò�������ֵ��");
		if (S_LEAnnotationReader::getInstance()->isPluginIncludedLengthParam(m_single_plugin->context)){		//����"xxx-10"�Ĳ��
			temp_list.push_back("����İ汾���ܱȽϾɡ�");
		}
		this->m_single_plugin->message = temp_list.join("\n");
		return false;
	}
	if (m_single_plugin->isIntegrity() == false){
		temp_list.push_back("����ṹ�����Դ������⣬����ȱ��޷��༭��");
		this->m_single_plugin->message = temp_list.join("\n");
		return false;
	}
	
	// > ��ȡ���������Ϣ
	QString paramMsg = "";
	QList<C_LEAnnotation_Param> params = m_single_plugin->paramList;
	for (int i = 0; i < params.count(); i++){
		C_LEAnnotation_Param param = params.at(i);
		paramMsg += param.getParamShowingName() + "��" + QString::number(param.getRealLen()) + "��";
		if (i != params.count()-1 ){
			paramMsg += ",";
		}
	}
	this->m_single_plugin->message = paramMsg;
	
	return true;
}
/*-------------------------------------------------
		���ļ� - ��ȡ�򿪺�Ĳ������
*/
C_LEAnnotation* S_LengthFlowManager::getLastSinglePlugin(){
	return m_single_plugin;
}
/*-------------------------------------------------
		���ļ� - �༭���
*/
void S_LengthFlowManager::editSingle(){
	if (m_single_plugin->isNull()){ return; }
	QJsonObject obj = this->editOneWithWindow(m_single_plugin, m_single_data);
	if (obj.empty()){ return; }

	// > ��� ���ļ� ������
	this->m_single_data = QList<C_LEConfigData>();

	// > ��������
	QList<C_LEAnnotation_Param> params = m_single_plugin->paramList;
	for (int i = 0; i < params.count(); i++){
		C_LEAnnotation_Param param = params.at(i);

		QString name_p = m_single_plugin->pluginName;
		QString name_c = param.getParamKey();
		int configLen = obj.value(name_p + name_c + "���ֵ").toString().toInt();

		C_LEConfigData data = C_LEConfigData();
		data.initParam(name_p, name_c, configLen);
		this->m_single_data.push_back(data);
	}
	
	// > ˢ����Ϣ
	QString message = "";
	for (int j = 0; j < m_single_data.count(); j++){
		C_LEConfigData data = m_single_data.at(j);
		message += data.getParamShowingName() + "��" + QString::number(data.getConfigLen()) + "��";
		if (j != m_single_data.count() - 1){
			message += ",";
		}
	}
	if (message != ""){
		//message = "<span style='color:#00aa00;'>�޸�Ϊ��" + message + "</span>";	//����Ϊ��stylesheet��
		message = "�޸�Ϊ��" + message;
	}
	m_single_plugin->editMessage = message;

}
/*-------------------------------------------------
		���ļ� - ִ���޸�
*/
void S_LengthFlowManager::executeSingle(){

	// > �����޸�
	for (int i = 0; i < m_single_data.count();i++){
		C_LEConfigData config = m_single_data.at(i);
		C_LEAnnotation_Param param = m_single_plugin->getParamByKey(config.getParamKey());

		QString context = S_LEConfigWriter::getInstance()->doOverwritePlugin(m_single_plugin->context, param, config);
		if (context == ""){ return; }
		m_single_plugin->context = context;
	}

	// > д��
	QTextCodec::codecForName("utf-8");
	QFile file_to(m_single_plugin->fullPath);
	if (!file_to.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		QMessageBox::warning(nullptr, "����", "�޷����ļ���", QMessageBox::Yes);
		return;
	}
	QTextStream streamFileOut(&file_to);
	streamFileOut.setCodec("UTF-8");
	streamFileOut.flush();
	streamFileOut << m_single_plugin->context;
	file_to.close();
	QMessageBox::information(nullptr, "��ʾ", "�޸ĳɹ���", QMessageBox::Yes);
	
	// > ���´򿪲��
	this->openSingle(m_single_plugin->fullPath);
	// > ��ձ༭��Ϣ
	this->m_single_data = QList<C_LEConfigData>();
}



/*-------------------------------------------------
		�����ļ� - ��
*/
void S_LengthFlowManager::openBatch(QString dir_name){
	QDir dir_from(dir_name);

	// > �ļ��б���
	QFileInfoList d_list = dir_from.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
	W_TipWaitBox waitBox("���������...");
	waitBox.show();

	for (int i = 0; i < d_list.count(); i++){
		QFileInfo info = d_list.at(i);
		if (info.suffix() != "js"){ continue; }
		
		C_LEAnnotation* plugin = this->openBatchOne(info.filePath());
		this->m_batch_pluginList.push_back(plugin);
	}
	waitBox.hide();

}
/*-------------------------------------------------
		�����ļ� - ��һ���ļ�
*/
C_LEAnnotation* S_LengthFlowManager::openBatchOne(QString file_name){

	C_LEAnnotation* plugin = S_LEAnnotationReader::getInstance()->readPlugin(QFileInfo(file_name));

	// > ������
	QStringList temp_list = QStringList();
	if (plugin->isForbidden() == true){
		temp_list.push_back("�ò����ֹ�༭���ֵ��");
		plugin->message = temp_list.join("\n");
		return plugin;
	}
	if (plugin->isEditable() == false){
		temp_list.push_back("δ�ҵ��ò�������ֵ��");
		if (S_LEAnnotationReader::getInstance()->isPluginIncludedLengthParam(plugin->context)){		//����"xxx-10"�Ĳ��
			temp_list.push_back("����İ汾���ܱȽϾɡ�");
		}
		plugin->message = temp_list.join("\n");
		return plugin;
	}
	if (plugin->isIntegrity() == false){
		temp_list.push_back("����ṹ�����Դ������⣬����ȱ��޷��༭��");
		plugin->message = temp_list.join("\n");
		return plugin;
	}

	// > ��ȡ���������Ϣ
	QString paramMsg = "";
	QList<C_LEAnnotation_Param> params = plugin->paramList;
	for (int j = 0; j < params.count(); j++){
		C_LEAnnotation_Param param = params.at(j);
		paramMsg += param.getParamShowingName() + "��" + QString::number(param.getRealLen()) + "��";
		if (j != params.count() - 1){
			paramMsg += ",";
		}
	}
	plugin->message = paramMsg;

	return plugin;
}

/*-------------------------------------------------
		�����ļ� - ��ȡ�򿪺�Ĳ������
*/
QList<C_LEAnnotation*> S_LengthFlowManager::getLastBatchPlugin(){
	return m_batch_pluginList;
}
/*-------------------------------------------------
		�����ļ� - �༭���
*/
void S_LengthFlowManager::editBatchOne(C_LEAnnotation* plugin){
	if (!plugin->message.contains("��")){ return; }
	
	QJsonObject obj = this->editOneWithWindow(plugin, this->getBatchConfigDataByPlugin(plugin));
	if (obj.empty()){ return; }

	QList<C_LEAnnotation_Param> params = plugin->paramList;
	for (int i = 0; i < params.count(); i++){
		C_LEAnnotation_Param param = params.at(i);

		QString name_p = plugin->pluginName;
		QString name_c = param.getParamKey();
		int configLen = obj.value(name_p + name_c + "���ֵ").toString().toInt();

		C_LEConfigData data = C_LEConfigData();
		data.initParam(name_p, name_c, configLen);
		this->m_batch_dataList.removeOne(data);		//�Ƴ���ͬ�Ķ���
		this->m_batch_dataList.push_back(data);
		this->m_batch_storageList.removeOne(data);
		this->m_batch_storageList.push_back(data);

	}

	this->refreshBatchEditMessage();
}

/*-------------------------------------------------
		�����ļ� - ִ���޸�
*/
void S_LengthFlowManager::executeBatch(){
	W_TipWaitBox waitBox("����޸���...");
	waitBox.show();
	for (int i = 0; i < m_batch_pluginList.count(); i++){
		C_LEAnnotation* plugin = m_batch_pluginList.at(i);
		QList<C_LEConfigData> config_list = this->getBatchConfigDataByPlugin(plugin);
		if (config_list.count() == 0){ continue; }

		// > �����޸�
		for (int j = 0; j < config_list.count(); j++){
			C_LEConfigData config = config_list.at(j);
			C_LEAnnotation_Param param = plugin->getParamByKey(config.getParamKey());

			QString context = S_LEConfigWriter::getInstance()->doOverwritePlugin(plugin->context, param, config);
			if (context == ""){ break; }
			plugin->context = context;
		}

		// > д��
		QTextCodec::codecForName("utf-8");
		QFile file_to(plugin->fullPath);
		if (!file_to.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			QMessageBox::warning(nullptr, "����", "�޷����ļ���", QMessageBox::Yes);
			return;
		}
		QTextStream streamFileOut(&file_to);
		streamFileOut.setCodec("UTF-8");
		streamFileOut.flush();
		streamFileOut << plugin->context;
		file_to.close();

		// > ����������
		plugin = this->openBatchOne(plugin->fullPath);
		m_batch_pluginList.replace(i, plugin);
	}

	// > ˢ�±༭����
	this->m_batch_dataList.clear();
	this->refreshBatchEditMessage();
	waitBox.hide();
	QMessageBox::information(nullptr, "��ʾ", "�޸ĳɹ���", QMessageBox::Yes);
}


/*-------------------------------------------------
		�����ļ� - ��������
*/
void S_LengthFlowManager::importConfig(){

	// > ѡ���ļ�
	QFileDialog fd;
	QString importFile;
	fd.setWindowTitle(("�������ֵ����"));
	fd.setAcceptMode(QFileDialog::AcceptOpen);
	fd.setNameFilters(QStringList() << ("���ֵ����(*.drillle)"));
	fd.setViewMode(QFileDialog::Detail);
	if (fd.exec() == QDialog::Accepted) {
		if (fd.selectedFiles().empty()) {
			return;
		}
		importFile = fd.selectedFiles().at(0);
	}
	else{
		return;
	}

	// > ���ļ�
	QFile input_file(importFile);
	if (!input_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "����", "�޷����ļ���", QMessageBox::Yes);
	}
	QTextStream in(&input_file);
	QString context = in.readAll();				//��ȡ��input�ļ�����������

	// > ����json
	QJsonDocument jsonDocument = QJsonDocument::fromJson(context.toUtf8());
	if (jsonDocument.isNull()){
		QMessageBox::warning(nullptr, "����", "��ȡ�ļ�ʧ�ܡ�", QMessageBox::Yes);
		return;
	}

	// > ����ת��
	QJsonObject obj_all = jsonDocument.object();
	QString obj_type = obj_all.value("dataType").toString();
	if (obj_type != "drill_LE_config"){
		QMessageBox::warning(nullptr, "����", "�ļ���ʽ����ȷ����ѡ��������Ч�ļ���", QMessageBox::Yes);
		return;
	}
	this->m_batch_dataList.clear();
	QJsonArray obj_arr = obj_all.value("dataList").toArray();
	for (int i = 0; i < obj_arr.count(); i++){
		QJsonObject data_obj = obj_arr.at(i).toObject();

		C_LEConfigData data = C_LEConfigData();
		data.setJsonObject(data_obj);
		this->m_batch_dataList.removeOne(data);		//�Ƴ���ͬ�Ķ���
		this->m_batch_dataList.push_back(data);
		this->m_batch_storageList.removeOne(data);
		this->m_batch_storageList.push_back(data);
	}

	// > ˢ�±༭����
	this->refreshBatchEditMessage();
}
/*-------------------------------------------------
		�����ļ� - ��������
*/
void S_LengthFlowManager::exportConfig(){

	// > ѡ���ļ�
	QFileDialog fd;
	QString exportFile;
	fd.setWindowTitle(("�������ֵ����"));
	fd.setAcceptMode(QFileDialog::AcceptSave);
	fd.setNameFilters(QStringList() << ("���ֵ����(*.drillle)"));
	fd.selectFile("rmmv���ֵ����.drillle");
	fd.setViewMode(QFileDialog::Detail);
	if (fd.exec() == QDialog::Accepted) {
		if (fd.selectedFiles().empty()) {
			return;
		}
		exportFile = fd.selectedFiles().at(0);
	}
	else{
		return;
	}

	// > ��д����ļ�
	QFile file_to(exportFile);
	if (!file_to.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		QMessageBox::warning(nullptr, "����", "�޷����ļ���", QMessageBox::Yes);
	}

	// > ����ת����storageList���ܴ󲿷�clearӰ�죩
	QJsonArray obj_arr = QJsonArray();
	for (int i = 0; i < m_batch_storageList.count(); i++){
		C_LEConfigData data = m_batch_storageList.at(i);
		obj_arr.append(data.getJsonObject());
	}
	QJsonObject obj_all = QJsonObject();
	obj_all.insert("dataType", "drill_LE_config");
	obj_all.insert("dataList", obj_arr);

	// > д��
	QString context_all = QJsonDocument(obj_all).toJson();
	file_to.write(context_all.toLocal8Bit());
	file_to.close();
}



/*-------------------------------------------------
		�����ļ� - �򿪴��ڱ༭���
*/
QJsonObject S_LengthFlowManager::editOneWithWindow(C_LEAnnotation* plugin, QList<C_LEConfigData> data_list){
	if (plugin->isNull()){ return QJsonObject(); }

	// > ������׼��
	C_FastClass data_class = C_FastClass("�������");
	//C_FastClass temp_class = C_FastClass("�����Ϣ");
	//temp_class.addQString("�����", plugin->pluginName);
	//temp_class.setParamShowingName("�����", "�����");
	//temp_class.setParamEditable("�����", false);
	//temp_class.addQString("������", plugin->pluginDesc);
	//temp_class.setParamShowingName("������", "������");
	//temp_class.setParamEditable("������", false);
	//temp_class.addQString("�������", plugin->pluginAuthor);
	//temp_class.setParamShowingName("�������", "����");
	//temp_class.setParamEditable("�������", false);
	//data_class.addFastClassQWidget(temp_class);
	QList<C_LEAnnotation_Param> params = plugin->paramList;
	for (int i = 0; i < params.count(); i++){
		C_LEAnnotation_Param param = params.at(i);

		// > Ĭ��ֵ
		QString name_p = plugin->pluginName;
		QString name_c = param.getParamKey();
		QString var_len = QString::number(param.getRealLen());

		C_FastClass temp_class = C_FastClass(name_c.split("-").at(0));
		temp_class.addInt					(name_p + name_c + "���ֵ", var_len);		//���������ƣ���ֹ�ظ���
		temp_class.setParamShowingName		(name_p + name_c + "���ֵ", "���ֵ");
		
		// > Ĭ�����ݸ���
		for (int i = 0; i < data_list.count(); i++){
			C_LEConfigData data = data_list.at(i);
			if (name_p == data.getPluginName() && name_c == data.getParamKey()){
				temp_class.setParamDefaultValue(name_p + name_c + "���ֵ", QString::number(data.getConfigLen()));
			}
		}

		data_class.addFastClassQGroupBox(temp_class);
	}


	// > ���������ݻ�ȡ + ����
	W_FastWindow d;
	d.setDataInAddMode(data_class);
	d.setWindowTitle("�������ֵ");
	if (d.exec() == QDialog::Accepted) {
		QJsonObject p = d.getData();
		return p;
	}

	return QJsonObject();
}
/*-------------------------------------------------
		�����ļ� - �������û�ȡ�����
*/
QList<C_LEConfigData> S_LengthFlowManager::getBatchConfigDataByPlugin(C_LEAnnotation* plugin){
	QList<C_LEConfigData> result_list = QList<C_LEConfigData>();
	for (int i = 0; i < this->m_batch_dataList.count(); i++){
		C_LEConfigData data = this->m_batch_dataList.at(i);
		if (data.getPluginName() == plugin->pluginName){

			for (int j = 0; j < plugin->paramList.count(); j++){
				C_LEAnnotation_Param param = plugin->paramList.at(j);
				if (data.getParamKey() == param.getParamKey()){
					result_list.push_back(data);
					break;
				}
			}
		}
	}
	return result_list;
}
/*-------------------------------------------------
		�����ļ� - ˢ�±༭��Ϣ
*/
void S_LengthFlowManager::refreshBatchEditMessage(){
	for (int i = 0; i < m_batch_pluginList.count(); i++){
		C_LEAnnotation* plugin = m_batch_pluginList.at(i);
		QList<C_LEConfigData> data_list = this->getBatchConfigDataByPlugin(plugin);
		if (data_list.count() == 0){ continue; }

		// > ˢ�µ�����༭��Ϣ
		QString message = "";
		for (int j = 0; j < data_list.count(); j++){
			C_LEConfigData data = data_list.at(j);
			message += data.getParamShowingName() + "��" + QString::number(data.getConfigLen()) + "��";
			if (j != data_list.count() - 1){
				message += ",";
			}
		}
		if (message != ""){
			//message = "<span style='color:#00aa00;'>�޸�Ϊ��" + message + "</span>";	//����Ϊ��stylesheet��
			message = "�޸�Ϊ��" + message ;
		}
		plugin->editMessage = message;
	}
}