#include <iostream>
#include <fstream>
#include <string>
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
#include "identity.h"
using namespace std;

// 添加全局函数_1.管理员进入子菜单界面
// 父类的指针接收, 父类指针对象的引用，此处可写为 (Identity* &manager)
void managerMenu(Identity* manager)
{
	while (true)
	{
		// 管理员菜单， 父类的指针虽然可以接收子类的对象，但调用时，只能调用父类和子类共有的接口，
		// 若需调用子类独有接口， 需将父类指针转换成子类指针
		manager->operMenu();

		// 父类指针转换为子类指针
		Manager* man = (Manager*)manager;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			// 添加账号
			man->addPerson();
		}
		else if (select == 2)
		{
			// 查看账号
			man->showPerson();
		}
		else if (select == 3)
		{
			// 查看机房
			man->showComputer();
		}
		else if (select == 4)
		{
			// 清空预约
			cout << "清空预约！" << endl;
			man->cleanFile();
		}
		else
		{
			// 注销功能
			// 删除堆区空间
			// delete manager;
			delete man;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	
}
// 添加全局函数_2.学生进入子菜单界面
// 父类指针接收子类对象
void studentMenu(Identity* &stu)
{
	// 接收信息
	int select = 0;
	// 父类指针转换为子类指针
	while (true)
	{
		// 进入学生菜单
		stu->operMenu();
		// 将父类指针强制装换为子类指针
		Student* stu_change = (Student*)stu;
		cin >> select;
		switch (select)
		{
		case 1:
			// 申 请  预 约  
			stu_change->applyOrder();
			break;
		case 2:
			// 查看我的预约
			stu_change->showMyOrder();
			break;
		case 3:
			// 查看所有预约
			stu_change->showAllOrder();
			break;
		case 4:
			// 取消预约
			stu_change->cancelOrder();
			break;
		case 0:
			// 注 销  登 录
			delete stu;
			cout << "注销成功， 欢迎下次使用！" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
// 添加全局函数_3.教师进入子菜单界面
// 父类指针接收子类对象
// void teacherMenu(Teacher* &teac)这里为什么不可以直接用子类指针传递？
void teacherMenu(Identity* &teac)
{
	int select = 0;
	// 父类指针转换为子类指针
	Teacher* teac_change = (Teacher*)teac;
	while (true)
	{
		// 进入教师菜单
		teac_change->operMenu();
		cin >> select;
		switch (select)
		{
		case 1:
			// 查看所有预约
			teac_change->showAllOrder();
			break;
		case 2:
			// 审核预约
			teac_change->validOrder();
			break;
		case 0:
			// 注 销  登 录	
			// teac和teac_change此时因为强转换，可以理解是同一个指针
			delete teac;
			// delete teac_change;	
			cout << "注销成功， 欢迎下次使用！" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// 添加登录全局函数(需操作文件的名称， 操作身份的类型)
void LoginIn(string fileName, int type)
{
	// 创建父类的指针，指向子类的创建的对象
	Identity* person = NULL;

	// 读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	// 判断是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	
	// 准备接收用户信息
	int id = 0;
	string name;
	string pwd;

	// 判断登录身份
	if (type == 1)
	{
		cout << "请输入你的学号： ";
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入你的教师编号： ";
		cin >> id;
	}

	cout << "请输入用户名： ";
	cin >> name;

	cout << "请输入密码： ";
	cin >> pwd;

	// 身份的验证
	if (type == 1)
	{
		// 学生身份的验证
		// 判断文件中读取的信息和输入的是否相等
		int file_id;
		string file_name;
		string file_pwd;

		while (ifs >> file_id&&ifs >> file_name&&ifs >> file_pwd)
		{
			if (file_name == name&&file_id == id&&file_pwd == pwd)
			{
				cout << "学生身份登录成功！！！" << endl;
				system("pause");
				system("cls");

				// 创建学生对象, 由父类指针在堆区，申请内存
				person = new Student(id, name, pwd);
				// 进入学生身份的子菜单操作
				studentMenu(person);
				return;
			}

		}
	}
	else if (type == 2)
	{
		// 教师身份的验证
		int file_id;
		string file_name;
		string file_pwd;

		while (ifs >> file_id&&ifs >> file_name&&ifs >> file_pwd)
		{
			if (file_id == id&&file_name == name&&file_pwd == pwd)
			{
				cout << "教师身份登录成功！！！" << endl;
				system("pause");
				system("cls");
				// 创建老师对象, 由父类指针在堆区，申请内存
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;

			}
		}
	}
	else if (type == 3)
	{
		// 管理员身份的验证
		string file_name;
		string file_pwd;

		while (ifs >> file_name&&ifs >> file_pwd)
		{
			if (file_name == name&&file_pwd == pwd)
			{
				cout << "管理员身份登录成功！！！" << endl;
				system("pause");
				system("cls");
				// 创建管理员对象，进入管理员菜单
				person = new Manager(name, pwd);
				managerMenu(person);

				return;
			}
		}
	}

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}

int main()
{
	int select = 0;

	while (true)
	{
		cout << "\t\t############################\n";
		cout << "\t\t### 欢迎使用机房预约系统 ###\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       1. 学    生        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       2. 老    师        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       3. 管 理 园        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       0. 退    出        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t############################\n";
		cout << "请输入你的登录选择： ";

		cin >> select;
		switch (select)
		{
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //  退出功能
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误， 请重新输入!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}