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
	cout << "��ӭ��ʦ�� " << this->m_Name << "��¼��" << endl;
	cout << "\t\t############################\n";
	cout << "\t\t############################\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      1. �鿴����ԤԼ     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      2. �� ��  Ԥ Լ     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      0. ע ��  �� ¼     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t############################\n";
	cout << "��������Ĳ���ѡ�� ";
}
// �鿴����ԤԼ
void Teacher::showAllOrder()
{
	// ����ѧ����Ľӿ�
	Student stu;
	// ֱ�ӵ�����һ��Сbug�� ��ӭ��Ϣ�������޷�������ʾ,�˵���ʾ��Ҳ��ѧ���ġ���������������֪��զ��
	stu.showAllOrder();
}
// ���ԤԼ
void Teacher::validOrder()
{
	// ʵ������ͬѧ����
	// �ȴ�����������������˶������������У�����keyֵ�޸�value���ԣ��������ļ��ĸ��º��������浽�ļ���
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˵ļ�¼���£�" << endl;
	vector<int> v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << ">:";
			cout << "ԤԼʱ���; ��" << of.m_orderData[i]["date"];
			cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ѧ�ţ�" << of.m_orderData[i]["stu_id"];
			cout << " ������" << of.m_orderData[i]["stu_name"];
			cout << " ������" << of.m_orderData[i]["room_id"];
			// ״̬-ƴ���ַ���
			string status = " ״̬�������";
			cout << status << endl;
		}
	}
	cout << "��������˵�ԤԼ��¼��0������" << endl;
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
				cout << "��������˽��" << endl;
				cout << "1. ͨ��" << endl;
				cout << "2. ��ͨ��" << endl;
				cin >> ret;
				if (ret == 1)
				{
					// ͨ�����
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					// ��ͨ�����
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "�����ϣ�" << endl;
				break;
			}
		}
		cout << "�����������������룡" << endl;
	}
	system("pause");
	system("cls");

}