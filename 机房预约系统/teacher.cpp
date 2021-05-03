#include "teacher.h"

Teacher::Teacher()
{
}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

Teacher::~Teacher()
{
}

void Teacher::operMenu()
{
	cout << "欢迎老师： " << this->m_Name << "登录！" << endl;
	cout << "\t\t############################\n";
	cout << "\t\t############################\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      1. 查看所有预约     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      2. 审 核  预 约     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      0. 注 销  登 录     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t############################\n";
	cout << "请输入你的操作选择： ";
}
// 查看所有预约
void Teacher::showAllOrder()
{
	// 调用学生类的接口
	Student stu;
	// 直接调用有一个小bug， 欢迎信息，名字无法正常显示,菜单显示的也是学生的。。。？？？，不知道咋改
	stu.showAllOrder();
}
// 审核预约
void Teacher::validOrder()
{
	// 实现流程同学生类
	// 先创建容器，读出可审核对象，再在容器中，利用key值修改value属性，最后调用文件的更新函数，保存到文件中
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的记录如下：" << endl;
	vector<int> v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << ">:";
			cout << "预约时间段; 周" << of.m_orderData[i]["date"];
			cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 学号：" << of.m_orderData[i]["stu_id"];
			cout << " 姓名：" << of.m_orderData[i]["stu_name"];
			cout << " 机房：" << of.m_orderData[i]["room_id"];
			// 状态-拼接字符串
			string status = " 状态：审核中";
			cout << status << endl;
		}
	}
	cout << "请输入审核的预约记录，0代表返回" << endl;
	int select = 0;
	int ret = 0;

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果" << endl;
				cout << "1. 通过" << endl;
				cout << "2. 不通过" << endl;
				cin >> ret;
				if (ret == 1)
				{
					// 通过情况
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					// 不通过情况
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");

}