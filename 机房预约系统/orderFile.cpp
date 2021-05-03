#include "orderFile.h"

map<string, string> SplitData(string data)
{
	// 记录分割好的数值，并保存进容器
	string key, value;
	map<string, string> temp;
	// 此时取出的信息为key：value,可根据":"位置进行分割
	int pos = data.find(":");
	if (pos != -1)
	{
		// 没找到"："时，返回-1
		// substr分割函数,(开始截断位置， 截断个数)
		key = data.substr(0, pos);
		value = data.substr(pos + 1, data.size() - pos - 1);
		// 打印
		// cout << "key：" << key << endl;
		// cout << "value：" << value << endl;
	}	
	// 存入容器
	temp.insert(make_pair(key, value));
	

	return temp;
}

OrderFile::OrderFile()
{
	// 定义变量接收文件中信息
	string stu_id, stu_name, date, interval, room_id, status;

	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在或无预约记录！" << endl;
		system("pause");
		system("cls");
	}
	// 初始化容器,和条数
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
		// 此时取出的信息为key：value,可根据":"位置进行分割
		// cout << data << interval << stu_id << stu_name << room_id << status << endl;
		// string key, value;
		map<string, string> res_all;
		map<string, string> res_single;
		for (vector<string> ::iterator it = data_list.begin(); it != data_list.end(); it++)
		{
			res_single = SplitData(*it);
			// 将返回的容器合并到大map容器
			res_all.insert(res_single.begin(), res_single.end());
		}
		// cout << res_all.size() << endl;
		this->m_orderData.insert(make_pair(this->m_Size, res_all));
		// 容器清零
		data_list.clear();
		res_all.clear();

		this->m_Size++;
	}
	ifs.close();
	// 测试m_orderData容器
	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
	{
		cout << "个数= " << it->first << " value= " << endl;
		for (map<string, string>::iterator sub_it = (*it).second.begin(); sub_it != it->second.end(); sub_it++)
		{
			cout << " key= " << sub_it->first << " value= " << sub_it->second << " ";
		}
		cout << endl;
	}*/
}
// 更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		// 预约记录为0,直接返回
		return;
	}

	// 更新文件，即删除文件后创建新文件，并将容器中的文件依次写到新文件中
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