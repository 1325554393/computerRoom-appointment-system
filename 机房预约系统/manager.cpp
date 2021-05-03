#include "manager.h"

Manager::Manager()
{
}
Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_Name = name;
	this->m_Pwd = pwd;

	// ��ʼ������,��ȡ��ǰ״̬�£����صı�����˺���Ϣ
	this->initVector();
}

Manager::~Manager()
{
}

void Manager::operMenu()
{
	cout << "��ӭ����Ա�� " << this->m_Name << "��¼��" << endl;
	cout << "\t\t############################\n";
	cout << "\t\t############################\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       1. ����˺�        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       2. �鿴�˺�        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       3. �鿴����        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       4. ���ԤԼ        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|       0. ע����¼        |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t############################\n";
	cout << "��������Ĳ���ѡ�� ";

}
// ����˺�
void Manager::addPerson()
{
	cout << "����������˺�����" << endl;
	cout << "1. ���ѧ��" << endl;
	cout << "2. �����ʦ" << endl;

	int select = 0;
	// cin >> select;
	
	// �������ļ�������id�ţ�ѧ�źͽ�ʦ��ţ�
	string fileName;
	string tip_id;
	ofstream ofs;

	// �ظ�������ʾ
	string errorTip;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			// ����ѧ���ļ�������ʾ����ѧ��
			fileName = STUDENT_FILE;
			tip_id = "������ѧ�ţ� ";
			errorTip = "ѧ���ظ������������룡";
			break;
		}
		else if (select == 2)
		{
			// ������ʦ�ļ�������ʾ����ְ����
			fileName = TEACHER_FILE;
			tip_id = "������ְ���ţ� ";
			errorTip = "ְ�����ظ������������룡";
			break;
		}
		else
		{
			cout << "�����������������룡" << endl;
			// system("pause");
			//this->operMenu();
		}
	}

	// �Զ�����ļ����в���_׷�ӵķ�ʽд�ļ�
	ofs.open(fileName, ios::out | ios::app);

	// ������ӵ��˺���Ϣ
	int id;
	string name;
	string pwd;

	cout << tip_id << endl;
	// cin >> id;
	// ����ȥ�غ���
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
	cout << "������������ ";
	cin >> name;
	cout << "����������:  ";
	cin >> pwd;

	// ���ļ��������Ϣ
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << " �˺���ӳɹ���" << endl;

	system("pause");
	system("cls");

	ofs.close();

	// ���³�ʼ������,��ȡ��ǰ״̬�£����صı�����˺���Ϣ-�����¸���Ӻõ��˺ŵ������У�����������
	this->initVector();
}

// Ϊfor_each������������ӡ���ܺ���
void printStudent(Student &s)
{
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}
void printTeacher(Teacher &t)
{
	cout << "ְ���ţ�" << t.m_EmpId << " ������" << t.m_Name << " ���룺" << t.m_Pwd << endl;
}

// �鿴�˺�
void Manager::showPerson()
{
	cout << "������鿴�˺�����" << endl;
	cout << "1. �鿴ѧ��" << endl;
	cout << "2. �鿴��ʦ" << endl;

	int select = 0;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			cout << "����ѧ����Ϣ���£�" << endl;
			for_each(this->vStu.begin(), this->vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "������ʦ��Ϣ���£�" << endl;
			for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
			break;
		}
		else
		{
			cout << "�����������������룡" << endl;
		}
	}
	system("pause");
	system("cls");
}
// �鿴������Ϣ
void Manager::showComputer()
{
	cout << "���л�����Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{ 
		cout << "�������Ϊ��" << (*it).m_Comid << " ����Ϊ��" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
// ���ԤԼ��¼
void Manager::cleanFile()
{
	bool ret = this->checkClear();
	if (ret)
	{
		// ����ļ���
		ofstream ofs;
		// trunc ��պ���д����
		ofs.open(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "ԤԼ��ճɹ���" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "ȡ����գ�" << endl;
		system("pause");
		system("cls");
	}
}
// ��ʼ������
void Manager::initVector()
{
	// ������ʼ��
	vStu.clear();
	vTea.clear();

	// ��ȡ�˺���Ϣ- ѧ��
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		return;
	}
	// ����ѧ�����󣬽����˺���Ϣ
	// ע�ⴴ��һ��ѧ�����󼴿ɣ��ظ����ղ�ͬ���˺���Ϣ������push-back������
	Student s;
	while (ifs >> s.m_Id&&ifs >> s.m_Name&&ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();

	// ��ȡ�˺���Ϣ- ��ʦ
	// ifstream ifs; д�Ͼ����ض���
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		return;
	}
	// ������ʦ���󣬽����˺���Ϣ
	// ע�ⴴ��һ����ʦ���󼴿ɣ��ظ����ղ�ͬ���˺���Ϣ������push-back������
	Teacher t;
	while (ifs >> t.m_EmpId&&ifs >> t.m_Name&&ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();

	// ��ȡ������Ϣ
	// ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "������Ϣ�����ڣ�" << endl;
	}

	ComputerRoom comp;
	while (ifs >> comp.m_Comid&&ifs >> comp.m_MaxNum)
	{
		vCom.push_back(comp);
	}
	cout << "��ǰ��������Ϊ��" << vCom.size() << endl;
	ifs.close();
}
// ȥ�غ���-id��ȥ�أ� type���˺ŵ�����
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		// ����ѧ������
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
		// ������ʦ����
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
// ���ԤԼ��¼-�ж��Ƿ�ȷ�����
bool Manager::checkClear()
{
	cout << "ȷ�����ԤԼ��" << endl;
	cout << "1. ��" << endl;
	cout << "2. ��" << endl;
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
			cout << "�����������������룡" << endl;
		}
	}	
}

