#include "manager.h"

Manager::Manager()
{
}
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	// 初始化容器,获取当前状态下，本地的保存的账号信息
	this->initVector();
}

Manager::~Manager()
{
}

void Manager::operMenu()
{
	cout << "欢迎管理员： " << this->m_Name << "登录！" << endl;
	cout << "\t\t############################\n";
	cout << "\t\t############################\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       1. 添加账号        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       2. 查看账号        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       3. 查看机房        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       4. 清空预约        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       0. 注销登录        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t############################\n";
	cout << "请输入你的操作选择： ";

}
// 添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号类型" << endl;
	cout << "1. 添加学生" << endl;
	cout << "2. 添加老师" << endl;

	int select = 0;
	// cin >> select;
	
	// 操作的文件名，和id号（学号和教师编号）
	string fileName;
	string tip_id;
	ofstream ofs;

	// 重复错误提示
	string errorTip;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			// 接收学生文件，并提示输入学号
			fileName = STUDENT_FILE;
			tip_id = "请输入学号： ";
			errorTip = "学号重复，请重新输入！";
			break;
		}
		else if (select == 2)
		{
			// 接收老师文件，并提示输入职工号
			fileName = TEACHER_FILE;
			tip_id = "请输入职工号： ";
			errorTip = "职工号重复，请重新输入！";
			break;
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
			// system("pause");
			//this->operMenu();
		}
	}

	// 对读入的文件进行操作_追加的方式写文件
	ofs.open(fileName, ios::out | ios::app);

	// 接收添加的账号信息
	int id;
	string name;
	string pwd;

	cout << tip_id << endl;
	// cin >> id;
	// 调用去重函数
	// this->checkRepeat(id, select);
	while (true)
	{
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名： ";
	cin >> name;
	cout << "请输入密码:  ";
	cin >> pwd;

	// 向文件中添加信息
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << " 账号添加成功！" << endl;

	system("pause");
	system("cls");

	ofs.close();

	// 重新初始化容器,获取当前状态下，本地的保存的账号信息-即更新刚添加好的账号到容器中，避免二次添加
	this->initVector();
}

// 为for_each函数，创建打印功能函数
void printStudent(Student &s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher &t)
{
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}

// 查看账号
void Manager::showPerson()
{
	cout << "请输入查看账号类型" << endl;
	cout << "1. 查看学生" << endl;
	cout << "2. 查看老师" << endl;

	int select = 0;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			cout << "所有学生信息如下：" << endl;
			for_each(this->vStu.begin(), this->vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "所有老师信息如下：" << endl;
			for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
			break;
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
		}
	}
	system("pause");
	system("cls");
}
// 查看机房信息
void Manager::showComputer()
{
	cout << "所有机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{ 
		cout << "机房编号为：" << (*it).m_Comid << " 容量为：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
// 清空预约记录
void Manager::cleanFile()
{
	bool ret = this->checkClear();
	if (ret)
	{
		// 输出文件流
		ofstream ofs;
		// trunc 清空后，重写操作
		ofs.open(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "预约清空成功！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "取消清空！" << endl;
		system("pause");
		system("cls");
	}
}
// 初始化容器
void Manager::initVector()
{
	// 容器初始化
	vStu.clear();
	vTea.clear();

	// 读取账号信息- 学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		return;
	}
	// 创建学生对象，接收账号信息
	// 注意创建一个学生对象即可，重复接收不同的账号信息，依次push-back进容器
	Student s;
	while (ifs >> s.m_Id&&ifs >> s.m_Name&&ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	// 读取账号信息- 老师
	// ifstream ifs; 写上就是重定义
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		return;
	}
	// 创建老师对象，接收账号信息
	// 注意创建一个老师对象即可，重复接收不同的账号信息，依次push-back进容器
	Teacher t;
	while (ifs >> t.m_EmpId&&ifs >> t.m_Name&&ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "当前老师数量为：" << vTea.size() << endl;
	ifs.close();

	// 读取机房信息
	// ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "机房信息不存在！" << endl;
	}

	ComputerRoom comp;
	while (ifs >> comp.m_Comid&&ifs >> comp.m_MaxNum)
	{
		vCom.push_back(comp);
	}
	cout << "当前机房数量为：" << vCom.size() << endl;
	ifs.close();
}
// 去重函数-id号去重， type是账号的类型
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		// 遍历学生容器
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == (*it).m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		// 遍历老师容器
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}
// 清空预约记录-判断是否确认清空
bool Manager::checkClear()
{
	cout << "确认清空预约？" << endl;
	cout << "1. 是" << endl;
	cout << "2. 否" << endl;
	int select = 0;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			return true;
		}
		else if (select == 2) return false;
		else
		{
			cout << "输入有误，请重新输入！" << endl;
		}
	}	
}

