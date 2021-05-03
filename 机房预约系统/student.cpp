#include "student.h"

Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
	// 初始化参数
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	// 初始化容器
	this->initVector();
}

Student::~Student()
{

}

// 菜单函数 需重写基类中的纯虚函数，否则子类依旧是虚类 无法实例化对象
void Student::operMenu()
{
	cout << "欢迎学生： " << this->m_Name << "登录！" << endl;
	cout << "\t\t############################\n";
	cout << "\t\t############################\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      1. 申 请  预 约     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      2. 查看我的预约     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      3. 查看所有预约     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      4. 取 消  预 约     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      0. 注 销  登 录     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t############################\n";
	cout << "请输入你的操作选择： ";
}

// 申请预约
void Student::applyOrder()
{
	int data = 0, interval = 0, room = 0;

	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1. 周一 " << " 2. 周二 " << " 3. 周三 " << " 4. 周四 " << " 5. 周五 " << endl;
	while (true)
	{
		cin >> data;
		if (data >= 1 && data <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;
	cout << "1. 上午 "<< endl;
	cout << "2. 下午 " << endl;
	while (true)
	{
		cin >> interval;
		if (interval > 0 && interval < 3)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	cout << "请选择机房：" << endl;
	/*cout << "1号机房容量 " << vCom[0].m_MaxNum << endl;
	cout << "2号机房容量 " << vCom[1].m_MaxNum << endl;
	cout << "3号机房容量 " << vCom[2].m_MaxNum << endl;*/
	for (int i = 0; i < this->vCom.size(); i++)
	{
		cout <<vCom[i].m_Comid <<"号机房容量 " << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room > 0 && room < 4)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "预约成功！审核中。。。" << endl;

	// 将预约信息保存到文件中
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << data << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stu_id:" << this->m_Id << " ";
	ofs << "stu_name:" << this->m_Name << " ";
	ofs << "room_id:" << room << " ";
	// 预约状态可设计为 1.审核中2.预约成功-1.预约失败0.预约已取消
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

// 查看我的预约
void Student::showMyOrder()
{
	// 记录个人预约次数
	int count = 0;
	OrderFile orderfile;
	if (orderfile.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.m_Size; i++)
	{
		// 这里注意两边类型不一致，需类型转换 atoi...c_str() string类型强制转为int类型
		if (this->m_Id == atoi(orderfile.m_orderData[i]["stu_id"].c_str()))
		{
			cout << "预约时间段; 周" << orderfile.m_orderData[i]["date"];
			// 判断表达式
			cout << " 时段; " << (orderfile.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房; " << orderfile.m_orderData[i]["room_id"];
			// 设计审核状态 1.审核中2.预约成功-1.预约失败0.预约已取消
			string status = "状态: ";
			if (orderfile.m_orderData[i]["status"] == "1")
			{
				status += "审核中。。。";
			}
			else if (orderfile.m_orderData[i]["status"] == "2")
			{
				status += "预约成功！";
			}
			else if (orderfile.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败！";
			}
			else
			{
				status += "预约已取消！";
			}
			cout << status << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "无预约记录!" << endl;
	}
	system("pause");
	system("cls");
}

// 查看所有预约
void Student::showAllOrder()
{
	OrderFile ordf;
	if (ordf.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < ordf.m_Size; i++)
	{
		cout << i + 1 << " ";
		cout << "预约时间段; 周" << ordf.m_orderData[i]["date"];
		cout << " 时段：" << (ordf.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << ordf.m_orderData[i]["stu_id"];
		cout << " 姓名：" << ordf.m_orderData[i]["stu_name"];
		cout << " 机房：" << ordf.m_orderData[i]["room_id"];
		// 状态-拼接字符串
		string status = "状态：";
		if (ordf.m_orderData[i]["status"] == "1")
		{
			status += "审核中。。。";
		}
		else if (ordf.m_orderData[i]["status"] == "2")
		{
			status += "预约成功！";
		}
		else if (ordf.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败！";
		}
		else
		{
			status += "预约已取消！";
		}
		cout << status << endl;
		cout << endl;
		// 分页显示
		if ((i+1) % 3 == 0)
		{
			if (i + 1 == ordf.m_Size)
			{
				cout << "查看完毕！" << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "按任意键,查看下一页" << endl;
				system("pause");
				system("cls");
				// 后续中teacher类的调用，会让下面这行出现显示菜单不对，故注释，目前不知道咋改
				// this->operMenu();
				// cout << endl;
			}			
		}	
	}
}

// 取消预约
void Student::cancelOrder()
{
	OrderFile ordf;
	// 判断预约是否为空
	if (0 == ordf.m_Size)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	// 提示信息
	cout << "<<只有审核中或预约成功的记录可以取消>>" << endl;

	// 找出自己的可修改的预约记录
	// 创建容器，记录自己预约的编号
	vector<int> record;
	int idx=1;
	for (int i = 0; i < ordf.m_Size; i++)
	{
		if (this->m_Id == atoi(ordf.m_orderData[i]["stu_id"].c_str()))
		{
			if ("1" == ordf.m_orderData[i]["status"] || "2" == ordf.m_orderData[i]["status"])
			{
				record.push_back(i);
				// idx++起始值为idx， ++idx起始值为idx+1
				cout << idx++ << "> ";
				cout << "预约时间段; 周" << ordf.m_orderData[i]["date"];
				cout << " 时段; " << (ordf.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房; " << ordf.m_orderData[i]["room_id"];
				// 状态-拼接字符串
				string status = "状态：";
				if (ordf.m_orderData[i]["status"] == "1")
				{
					status += "审核中。。。";
				}
				else if (ordf.m_orderData[i]["status"] == "2")
				{
					status += "预约成功！";
				}
				cout << status << endl;
			}
		}
	}
	// tips
	cout << "请输入取消的记录： " ;
	int select = 0;

	while (true)
	{
		cin >> select;
		if (select > -1 && select < record.size()+1)
		{
			if (select == 0)
			{
				break;
			}
			else
			{	// record里面的索引值按顺序排列，因此可以按顺序检索到
				ordf.m_orderData[record[select - 1]]["status"] = "0";
				// 容器更新完毕后 ，重新写入文件
				ordf.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	system("pause");
	system("cls");
}
// 初始化容器
void Student::initVector()
{
	// 获取机房信息,并保存在机房容器中
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom comp;
	while (ifs >> comp.m_Comid&&ifs >> comp.m_MaxNum)
	{
		this->vCom.push_back(comp);
	}
	ifs.close();
}