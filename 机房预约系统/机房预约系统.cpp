#include <iostream>
#include <fstream>
#include <string>
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
#include "identity.h"
using namespace std;

// ���ȫ�ֺ���_1.����Ա�����Ӳ˵�����
// �����ָ�����, ����ָ���������ã��˴���дΪ (Identity* &manager)
void managerMenu(Identity* manager)
{
	while (true)
	{
		// ����Ա�˵��� �����ָ����Ȼ���Խ�������Ķ��󣬵�����ʱ��ֻ�ܵ��ø�������๲�еĽӿڣ�
		// �������������нӿڣ� �轫����ָ��ת��������ָ��
		manager->operMenu();

		// ����ָ��ת��Ϊ����ָ��
		Manager* man = (Manager*)manager;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			// ����˺�
			man->addPerson();
		}
		else if (select == 2)
		{
			// �鿴�˺�
			man->showPerson();
		}
		else if (select == 3)
		{
			// �鿴����
			man->showComputer();
		}
		else if (select == 4)
		{
			// ���ԤԼ
			cout << "���ԤԼ��" << endl;
			man->cleanFile();
		}
		else
		{
			// ע������
			// ɾ�������ռ�
			// delete manager;
			delete man;
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	
}
// ���ȫ�ֺ���_2.ѧ�������Ӳ˵�����
// ����ָ������������
void studentMenu(Identity* &stu)
{
	// ������Ϣ
	int select = 0;
	// ����ָ��ת��Ϊ����ָ��
	while (true)
	{
		// ����ѧ���˵�
		stu->operMenu();
		// ������ָ��ǿ��װ��Ϊ����ָ��
		Student* stu_change = (Student*)stu;
		cin >> select;
		switch (select)
		{
		case 1:
			// �� ��  Ԥ Լ  
			stu_change->applyOrder();
			break;
		case 2:
			// �鿴�ҵ�ԤԼ
			stu_change->showMyOrder();
			break;
		case 3:
			// �鿴����ԤԼ
			stu_change->showAllOrder();
			break;
		case 4:
			// ȡ��ԤԼ
			stu_change->cancelOrder();
			break;
		case 0:
			// ע ��  �� ¼
			delete stu;
			cout << "ע���ɹ��� ��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
// ���ȫ�ֺ���_3.��ʦ�����Ӳ˵�����
// ����ָ������������
// void teacherMenu(Teacher* &teac)����Ϊʲô������ֱ��������ָ�봫�ݣ�
void teacherMenu(Identity* &teac)
{
	int select = 0;
	// ����ָ��ת��Ϊ����ָ��
	Teacher* teac_change = (Teacher*)teac;
	while (true)
	{
		// �����ʦ�˵�
		teac_change->operMenu();
		cin >> select;
		switch (select)
		{
		case 1:
			// �鿴����ԤԼ
			teac_change->showAllOrder();
			break;
		case 2:
			// ���ԤԼ
			teac_change->validOrder();
			break;
		case 0:
			// ע ��  �� ¼	
			// teac��teac_change��ʱ��Ϊǿת�������������ͬһ��ָ��
			delete teac;
			// delete teac_change;	
			cout << "ע���ɹ��� ��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// ��ӵ�¼ȫ�ֺ���(������ļ������ƣ� ������ݵ�����)
void LoginIn(string fileName, int type)
{
	// ���������ָ�룬ָ������Ĵ����Ķ���
	Identity* person = NULL;

	// ���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);
	// �ж��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	
	// ׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;

	// �жϵ�¼���
	if (type == 1)
	{
		cout << "���������ѧ�ţ� ";
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "��������Ľ�ʦ��ţ� ";
		cin >> id;
	}

	cout << "�������û����� ";
	cin >> name;

	cout << "���������룺 ";
	cin >> pwd;

	// ��ݵ���֤
	if (type == 1)
	{
		// ѧ����ݵ���֤
		// �ж��ļ��ж�ȡ����Ϣ��������Ƿ����
		int file_id;
		string file_name;
		string file_pwd;

		while (ifs >> file_id&&ifs >> file_name&&ifs >> file_pwd)
		{
			if (file_name == name&&file_id == id&&file_pwd == pwd)
			{
				cout << "ѧ����ݵ�¼�ɹ�������" << endl;
				system("pause");
				system("cls");

				// ����ѧ������, �ɸ���ָ���ڶ����������ڴ�
				person = new Student(id, name, pwd);
				// ����ѧ����ݵ��Ӳ˵�����
				studentMenu(person);
				return;
			}

		}
	}
	else if (type == 2)
	{
		// ��ʦ��ݵ���֤
		int file_id;
		string file_name;
		string file_pwd;

		while (ifs >> file_id&&ifs >> file_name&&ifs >> file_pwd)
		{
			if (file_id == id&&file_name == name&&file_pwd == pwd)
			{
				cout << "��ʦ��ݵ�¼�ɹ�������" << endl;
				system("pause");
				system("cls");
				// ������ʦ����, �ɸ���ָ���ڶ����������ڴ�
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;

			}
		}
	}
	else if (type == 3)
	{
		// ����Ա��ݵ���֤
		string file_name;
		string file_pwd;

		while (ifs >> file_name&&ifs >> file_pwd)
		{
			if (file_name == name&&file_pwd == pwd)
			{
				cout << "����Ա��ݵ�¼�ɹ�������" << endl;
				system("pause");
				system("cls");
				// ��������Ա���󣬽������Ա�˵�
				person = new Manager(name, pwd);
				managerMenu(person);

				return;
			}
		}
	}

	cout << "��֤��¼ʧ�ܣ�" << endl;
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
		cout << "\t\t### ��ӭʹ�û���ԤԼϵͳ ###\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       1. ѧ    ��        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       2. ��    ʦ        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       3. �� �� ԰        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t|       0. ��    ��        |\n";
		cout << "\t\t|                          |\n";
		cout << "\t\t############################\n";
		cout << "��������ĵ�¼ѡ�� ";

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
		case 0: //  �˳�����
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�������� ����������!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}