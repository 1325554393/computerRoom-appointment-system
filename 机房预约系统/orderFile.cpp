#include "orderFile.h"

map<string, string> SplitData(string data)
{
	// ��¼�ָ�õ���ֵ�������������
	string key, value;
	map<string, string> temp;
	// ��ʱȡ������ϢΪkey��value,�ɸ���":"λ�ý��зָ�
	int pos = data.find(":");
	if (pos != -1)
	{
		// û�ҵ�"��"ʱ������-1
		// substr�ָ��,(��ʼ�ض�λ�ã� �ضϸ���)
		key = data.substr(0, pos);
		value = data.substr(pos + 1, data.size() - pos - 1);
		// ��ӡ
		// cout << "key��" << key << endl;
		// cout << "value��" << value << endl;
	}	
	// ��������
	temp.insert(make_pair(key, value));
	

	return temp;
}

OrderFile::OrderFile()
{
	// ������������ļ�����Ϣ
	string stu_id, stu_name, date, interval, room_id, status;

	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڻ���ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
	}
	// ��ʼ������,������
	this->m_orderData.clear();
	this->m_Size = 0;

	while (ifs >> date&&ifs >> interval&&ifs >> stu_id&&ifs >> stu_name&&ifs >> room_id&&ifs >> status)
	{
		vector<string> data_list;
		data_list.push_back(date);
		data_list.push_back(interval);
		data_list.push_back(stu_id);
		data_list.push_back(stu_name);
		data_list.push_back(room_id);
		data_list.push_back(status);
		// ��ʱȡ������ϢΪkey��value,�ɸ���":"λ�ý��зָ�
		// cout << data << interval << stu_id << stu_name << room_id << status << endl;
		// string key, value;
		map<string, string> res_all;
		map<string, string> res_single;
		for (vector<string> ::iterator it = data_list.begin(); it != data_list.end(); it++)
		{
			res_single = SplitData(*it);
			// �����ص������ϲ�����map����
			res_all.insert(res_single.begin(), res_single.end());
		}
		// cout << res_all.size() << endl;
		this->m_orderData.insert(make_pair(this->m_Size, res_all));
		// ��������
		data_list.clear();
		res_all.clear();

		this->m_Size++;
	}
	ifs.close();
	// ����m_orderData����
	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
	{
		cout << "����= " << it->first << " value= " << endl;
		for (map<string, string>::iterator sub_it = (*it).second.begin(); sub_it != it->second.end(); sub_it++)
		{
			cout << " key= " << sub_it->first << " value= " << sub_it->second << " ";
		}
		cout << endl;
	}*/
}
// ����ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		// ԤԼ��¼Ϊ0,ֱ�ӷ���
		return;
	}

	// �����ļ�����ɾ���ļ��󴴽����ļ������������е��ļ�����д�����ļ���
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stu_id:" << this->m_orderData[i]["stu_id"] << " ";
		ofs << "stu_name:" << this->m_orderData[i]["stu_name"] << " ";
		ofs << "room_id:" << this->m_orderData[i]["room_id"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
	ofs.close();
}