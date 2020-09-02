#include "stdafx.h"
#include "s_LengthScanner.h"

#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#pragma execution_character_set("utf-8")


/*
-----==========================================================-----
		�ࣺ		�ı�ɨ����.h
		����ģ�飺	����ģ��
		���ܣ�		�ṩɨ�衢��дֱ�ӹ��ܡ�

		Ŀ�꣺		ʶ��������ı��������޸ģ�
						* @Drill_LE_param "����-%d"
						* @Drill_LE_parentKey "---������%d��%d---"
						* @Drill_LE_var "DrillUp.g_SSpA_context_list_length"

		˵����		����ֻ�ṩ��Ҫ�������ܡ�
					�����������ԵĽṹ��
					���������ݴ洢��ֻ��һ��ִ�й��ߡ�

-----==========================================================-----
*/

S_LengthScanner::S_LengthScanner() : QObject(){
	init();
}
S_LengthScanner::~S_LengthScanner() {
}
/*  - - ���� - - */
S_LengthScanner* S_LengthScanner::cur_manager = NULL;
S_LengthScanner* S_LengthScanner::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_LengthScanner();
	}
	return cur_manager;
}
/*  - - ��ʼ�� - - */
void S_LengthScanner::init() {

}

/*-------------------------------------------------
		ɨ�� - ��ȡ���� + ���ֵ
*/
C_LEPlugin* S_LengthScanner::doScanPlugin(QString file_name){
	C_LEPlugin* result = new C_LEPlugin();
	result->pluginName = QFileInfo(file_name).fileName();	//xxxx.js
	result->fullPath = QFileInfo(file_name).absoluteFilePath();

	// > �ļ���Դ
	QFile file_from(file_name);	
	if (!file_from.open(QFile::ReadOnly)){
		QMessageBox message(QMessageBox::Critical, ("����"), ("�޷����ļ�" + file_name ));
		message.exec();
		return result;
	}
	result->context = file_from.readAll();
	file_from.close();

	// > ɨ����׼��
	P_TxtFastReader reader = P_TxtFastReader(result->context);
	reader.prepare_trimAllRows();
	reader.prepare_replaceInStrings(QRegExp("( \\* )|( \\*)|(\\* )|(/\\*:)|(/\\*:ja)"), "");	//Ԥ��ȥ��ע��

	// > ��ȡ������
	int i_desc = reader.d_indexOf("@plugindesc", 0);
	if (i_desc != -1){
		QString desc_data = reader.d_rowAt(i_desc);
		result->pluginDesc = desc_data.replace("@plugindesc", "").trimmed();
	}

	// > ��ȡ�������
	int i_author = reader.d_indexOf("@author", 0);
	if (i_author != -1){
		QString author_data = reader.d_rowAt(i_author);
		result->pluginAuthor = author_data.replace("@author", "").trimmed();
	}

	// > ����������
	if (result->context.indexOf("@Drill_LE_editForbidden") != -1){
		result->paramForbidden = true;
		return result;
	}

	// > ��ȡ�������
	int length = reader.d_rowCount();
	QList<int> index_list = reader.d_getAllRowIndexsContains("@Drill_LE_param");
	for (int i = 0; i < index_list.length(); i++){
		int i_param = index_list.at(i);
		QString aaa = reader.d_rowAt(i_param + 1);
		QString bbb = reader.d_rowAt(i_param + 2);
		if (!reader.d_rowAt(i_param + 1).contains("@Drill_LE_parentKey")){ continue; }
		if (!reader.d_rowAt(i_param + 2).contains("@Drill_LE_var")){ continue; }

		// > ��ȡ�ַ�������ȥ�����ţ�
		QString s_param = reader.d_rowAt(i_param).replace("@Drill_LE_param", "");
		QString s_parentKey = reader.d_rowAt(i_param + 1).replace("@Drill_LE_parentKey", "");
		QString s_var = reader.d_rowAt(i_param + 2).replace("@Drill_LE_var", "");
		s_param = s_param.trimmed().replace("\"", "");
		s_parentKey = s_parentKey.trimmed().replace("\"", "");
		s_var = s_var.trimmed().replace("\"", "");

		// > ������
		C_LEPluginParam c_p = C_LEPluginParam();
		c_p.initParam(s_param, s_parentKey, s_var);
		result->paramList.push_back(c_p);
	}

	// > ��ȡ�������ֵ
	this->refreshScanPluginLenth(result);

	return result;
}
/*-------------------------------------------------
		ɨ�� - ˢ�²������ֵ
*/
void S_LengthScanner::refreshScanPluginLenth(C_LEPlugin* plugin){

	// > ɨ����׼��
	QString context = plugin->context;
	P_TxtFastReader reader = P_TxtFastReader(context);
	reader.prepare_trimAllRows();
	reader.prepare_replaceInStrings(QRegExp("( \\* )|( \\*)|(\\* )|(/\\*:)|(/\\*:ja)"), "");	//���е�ȥ��ע��

	// > ��ȡ - �������ֵ
	for (int i = 0; i < plugin->paramList.count(); i++){
		C_LEPluginParam pluginParam = plugin->paramList.at(i);
		QString var_str = pluginParam.getVarName();
		if (var_str == "" || var_str == "null"){ break; }

		QString re_str = var_str.replace(".", "\\.");		//��ֹ��ʶ������
		QRegExp re = QRegExp(re_str + "[ ]*=[^=]*");
		int i_var = context.indexOf(re, 0);
		int i_varEnd = context.indexOf("\n", i_var);
		if (i_var == -1){ continue; }
		if (i_varEnd == -1){ continue; }

		// > ����ֵ��ȡ
		QString data = context.mid(i_var, i_varEnd - i_var);
		QStringList dataList = data.split("=");
		if (dataList.count() == 0){ continue; }
		int var_length = TTool::_to_int_(dataList.at(1));	//եȡ�Ⱥź����intֵ

		pluginParam.setVarLen(var_length);
		plugin->paramList.replace(i, pluginParam);
	}

	// > ���� - ʵ�����ֵ
	for (int i = 0; i < plugin->paramList.count(); i++){
		C_LEPluginParam pluginParam = plugin->paramList.at(i);

		int real_length = 0; 
		QStringList param_names = reader.d_getAllRowsContains("@param");
		for (int j = 0; j < param_names.count(); j++){
			QString name = param_names.at(j);
			name = name.replace("@param", "").trimmed();
			
			QString match_str = pluginParam.getParamName(real_length + 1);
			if (match_str == name){
				real_length += 1;
			}
		}

		pluginParam.setRealLen(real_length);
		plugin->paramList.replace(i, pluginParam);
	}

}

/*-------------------------------------------------
		ɨ�� - ����Ƿ����"xxx-10"���и�ʽ
*/
bool S_LengthScanner::isPluginIncludedLengthParam(QString context){

	// > ɨ����׼��
	P_TxtFastReader reader = P_TxtFastReader(context);
	
	// > ʵ�ʱ�����������
	QStringList param_names = reader.d_getAllRowsContains(QRegExp("@param[ ]+.*-[0123456789]+"));
	return param_names.count() >= 4;
}


/*-------------------------------------------------
		��д - ���ֵ�޸�
*/
QString S_LengthScanner::doOverwritePlugin(QString context, C_LEPluginParam param, C_LEConfigData config){
	
	// > ���ֵ���
	if (config.getConfigLen() <= -1 ){
		QMessageBox::warning(nullptr, "����", "����Ҫ������" + config.getPluginName() + "�����ֵ��", QMessageBox::Yes);
		return "";
	}
	if (config.getConfigLen() <= 4){
		QMessageBox::warning(nullptr, "����", "���" + config.getPluginName() + "���������ֵ����С��4��", QMessageBox::Yes);
		return "";
	}
	// > ��ͬ���ֵ���޸�
	if (config.getConfigLen() == param.getRealLen()){ return context; }
	

	QStringList context_list = context.split(QRegExp("(\n\r)|(\n)|(\r\n)"));
	// -----------------------------
	// > �������������
	if (!param.isParentGrouping()){

		// > �ҵ�������ʼ��
		int i_param = 0;
		for (int i = 0; i < context_list.count(); i++){
			QString text = context_list.at(i);
			if (text.contains("@param") && text.contains(param.getParamName(1))){
				i_param = i;
				break;
			}
		}

		// > �ҵ���һ�������ṹ
		QStringList param_str_list = this->getParamStringList(context_list, param.getParamName(1));

		// > ��������ɾ����
		int name_index = param.getRealLen();
		bool deleteOn = false;
		for (int i = context_list.count() - 1; i >= i_param; i--){
			QString text = context_list.at(i);
			if (text.contains("@param") && text.contains(param.getParamName(name_index))){
				deleteOn = true;
				name_index--;
				context_list.removeAt(i);
				i++;
				continue;
			}
			if (deleteOn == true){
				if (text.contains("@") && !text.contains("@param")){
					context_list.removeAt(i);
					i++;
				}
				else{
					deleteOn = false;
				}
			}
		}

		// > ��������
		for (int i = 0; i < config.getConfigLen(); i++){
			QString data_str = param_str_list.join("\n");
			data_str = data_str.replace(param.getParamName(1), param.getParamName(i + 1));
			data_str = data_str.replace(QRegExp("@default[^\n]*"), "@default ");		//���Ĭ��ֵ
			data_str += "\n * ";
			context_list.insert(i_param + i, data_str);
		}


	// -----------------------------
	// > �����������
	}else{

		// > �ҵ�������ʼ��
		int i_param = 0;
		for (int i = 0; i < context_list.count(); i++){
			QString text = context_list.at(i);
			if (text.contains("@param") && text.contains(param.getParentName(1))){
				i_param = i;
				break;
			}
		}
		
		// > �ҵ���һ�������ṹ
		QStringList param_str_list = this->getParamStringList(context_list, param.getParamName(1));
		QStringList parent_str_list = this->getParamStringList(context_list, param.getParentName(1));

		// > ��������ɾ����
		int name_index = param.getRealLen();
		bool deleteOn = false;
		for (int i = context_list.count() - 1; i >= i_param; i--){
			QString text = context_list.at(i);
			if (text.contains("@param") && text.contains(param.getParamName(name_index))){
				deleteOn = true;
				name_index--;
				context_list.removeAt(i);
				i++;
				continue;
			}
			if (deleteOn == true){
				if (text.contains("@") && !text.contains("@param")){
					context_list.removeAt(i);
					i++;
				}
				else{
					deleteOn = false;
				}
			}
		}
		// > ��������ɾ������
		name_index = param.getRealLen();
		for (int i = context_list.count() - 1; i >= i_param; i--){
			QString text = context_list.at(i);
			if (text.contains("@param") && text.contains(param.getParentName(name_index))){
				deleteOn = true;
				name_index -= 20;
				context_list.removeAt(i);
				i++;
				continue;
			}
			if (deleteOn == true){
				if (text.contains("@") && !text.contains("@param")){
					context_list.removeAt(i);
					i++;
				}
				else{
					deleteOn = false;
				}
			}
		}


		// > ��������
		for (int i = 0; i < config.getConfigLen(); i++){
			QString parent_str = "";
			QString param_str = "";
			// > ����
			if (param.isParentGrouping() && i % 20 == 0){
				parent_str += parent_str_list.join("\n");
				parent_str = parent_str.replace(param.getParentName(1), param.getParentName(i + 1));
				parent_str += "\n * ";
				parent_str += "\n";
			}

			// > ����
			param_str += param_str_list.join("\n");
			param_str = param_str.replace(param.getParamName(1), param.getParamName(i + 1));
			param_str = param_str.replace(QRegExp("@default[^\n]*"), "@default ");		//���Ĭ��ֵ
			if (param.isParentGrouping()){	//parent�޸�
				param_str = param_str.replace(param.getParentName(1), param.getParentName(i + 1));
			}
			param_str += "\n * ";
			context_list.insert(i_param + i, parent_str + param_str);
		}
	}

	// > ���̶����Ǻ�
	QString result = context_list.join("\n");
	result = result.replace(QRegExp("([ \t\n\r]+\\*){5,}"),"\n * \n *");
	
	// > �滻
	QString var_str = param.getVarName();
	if (var_str != "" && var_str != "null"){
		QString re_str = var_str.replace(".", "\\.");		//��ֹ��ʶ������
		QRegExp re = QRegExp(re_str + "[ ]*=[^=]*\n");
		QString var_defineString = param.getVarName() + " = " + QString::number(config.getConfigLen()) + ";\n";
		result = result.replace(re, var_defineString);
	}

	return result;
}

/*-------------------------------------------------
		��д - ���� "�׶�-1" ��ȡ�� "@param �׶�-1" ��ȫ�������ַ���
*/
QStringList S_LengthScanner::getParamStringList(QStringList contextList, QString paramName){
	QStringList result_list = QStringList();
	bool finded = false;
	for (int i = 0; i < contextList.count(); i++){
		QString text = contextList.at(i);
		if (finded == false){
			if (text.contains("@param") && text.contains(paramName)){
				finded = true;
				result_list.append(text);
			}
		}
		else{	// finded == true
			if (text.contains("@")){
				result_list.append(text);
			}else{
				// > �ṹѰ�ҽ���
				break;
			}
		}
	}
	return result_list;
}