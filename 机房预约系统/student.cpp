#include "student.h"

Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
	// ��ʼ������
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	// ��ʼ������
	this->initVector();
}

Student::~Student()
{

}

// �˵����� ����д�����еĴ��麯���������������������� �޷�ʵ��������
void Student::operMenu()
{
	cout << "��ӭѧ���� " << this->m_Name << "��¼��" << endl;
	cout << "\t\t############################\n";
	cout << "\t\t############################\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      1. �� ��  Ԥ Լ     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      2. �鿴�ҵ�ԤԼ     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      3. �鿴����ԤԼ     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      4. ȡ ��  Ԥ Լ     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t|      0. ע ��  �� ¼     |\n";
	cout << "\t\t|                          |\n";
	cout << "\t\t############################\n";
	cout << "��������Ĳ���ѡ�� ";
}

// ����ԤԼ
void Student::applyOrder()
{
	int data = 0, interval = 0, room = 0;

	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1. ��һ " << " 2. �ܶ� " << " 3. ���� " << " 4. ���� " << " 5. ���� " << endl;
	while (true)
	{
		cin >> data;
		if (data >= 1 && data <= 5)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}

	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1. ���� "<< endl;
	cout << "2. ���� " << endl;
	while (true)
	{
		cin >> interval;
		if (interval > 0 && interval < 3)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}

	cout << "��ѡ�������" << endl;
	/*cout << "1�Ż������� " << vCom[0].m_MaxNum << endl;
	cout << "2�Ż������� " << vCom[1].m_MaxNum << endl;
	cout << "3�Ż������� " << vCom[2].m_MaxNum << endl;*/
	for (int i = 0; i < this->vCom.size(); i++)
	{
		cout <<vCom[i].m_Comid <<"�Ż������� " << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room > 0 && room < 4)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}
	cout << "ԤԼ�ɹ�������С�����" << endl;

	// ��ԤԼ��Ϣ���浽�ļ���
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << data << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stu_id:" << this->m_Id << " ";
	ofs << "stu_name:" << this->m_Name << " ";
	ofs << "room_id:" << room << " ";
	// ԤԼ״̬�����Ϊ 1.�����2.ԤԼ�ɹ�-1.ԤԼʧ��0.ԤԼ��ȡ��
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

// �鿴�ҵ�ԤԼ
void Student::showMyOrder()
{
	// ��¼����ԤԼ����
	int count = 0;
	OrderFile orderfile;
	if (orderfile.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.m_Size; i++)
	{
		// ����ע���������Ͳ�һ�£�������ת�� atoi...c_str() string����ǿ��תΪint����
		if (this->m_Id == atoi(orderfile.m_orderData[i]["stu_id"].c_str()))
		{
			cout << "ԤԼʱ���; ��" << orderfile.m_orderData[i]["date"];
			// �жϱ��ʽ
			cout << " ʱ��; " << (orderfile.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ����; " << orderfile.m_orderData[i]["room_id"];
			// ������״̬ 1.�����2.ԤԼ�ɹ�-1.ԤԼʧ��0.ԤԼ��ȡ��
			string status = "״̬: ";
			if (orderfile.m_orderData[i]["status"] == "1")
			{
				status += "����С�����";
			}
			else if (orderfile.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ���";
			}
			else if (orderfile.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ�";
			}
			else
			{
				status += "ԤԼ��ȡ����";
			}
			cout << status << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "��ԤԼ��¼!" << endl;
	}
	system("pause");
	system("cls");
}

// �鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile ordf;
	if (ordf.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < ordf.m_Size; i++)
	{
		cout << i + 1 << " ";
		cout << "ԤԼʱ���; ��" << ordf.m_orderData[i]["date"];
		cout << " ʱ�Σ�" << (ordf.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << ordf.m_orderData[i]["stu_id"];
		cout << " ������" << ordf.m_orderData[i]["stu_name"];
		cout << " ������" << ordf.m_orderData[i]["room_id"];
		// ״̬-ƴ���ַ���
		string status = "״̬��";
		if (ordf.m_orderData[i]["status"] == "1")
		{
			status += "����С�����";
		}
		else if (ordf.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ���";
		}
		else if (ordf.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ�";
		}
		else
		{
			status += "ԤԼ��ȡ����";
		}
		cout << status << endl;
		cout << endl;
		// ��ҳ��ʾ
		if ((i+1) % 3 == 0)
		{
			if (i + 1 == ordf.m_Size)
			{
				cout << "�鿴��ϣ�" << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "�������,�鿴��һҳ" << endl;
				system("pause");
				system("cls");
				// ������teacher��ĵ��ã������������г�����ʾ�˵����ԣ���ע�ͣ�Ŀǰ��֪��զ��
				// this->operMenu();
				// cout << endl;
			}			
		}	
	}
}

// ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile ordf;
	// �ж�ԤԼ�Ƿ�Ϊ��
	if (0 == ordf.m_Size)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	// ��ʾ��Ϣ
	cout << "<<ֻ������л�ԤԼ�ɹ��ļ�¼����ȡ��>>" << endl;

	// �ҳ��Լ��Ŀ��޸ĵ�ԤԼ��¼
	// ������������¼�Լ�ԤԼ�ı��
	vector<int> record;
	int idx=1;
	for (int i = 0; i < ordf.m_Size; i++)
	{
		if (this->m_Id == atoi(ordf.m_orderData[i]["stu_id"].c_str()))
		{
			if ("1" == ordf.m_orderData[i]["status"] || "2" == ordf.m_orderData[i]["status"])
			{
				record.push_back(i);
				// idx++��ʼֵΪidx�� ++idx��ʼֵΪidx+1
				cout << idx++ << "> ";
				cout << "ԤԼʱ���; ��" << ordf.m_orderData[i]["date"];
				cout << " ʱ��; " << (ordf.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " ����; " << ordf.m_orderData[i]["room_id"];
				// ״̬-ƴ���ַ���
				string status = "״̬��";
				if (ordf.m_orderData[i]["status"] == "1")
				{
					status += "����С�����";
				}
				else if (ordf.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ���";
				}
				cout << status << endl;
			}
		}
	}
	// tips
	cout << "������ȡ���ļ�¼�� " ;
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
			{	// record���������ֵ��˳�����У���˿��԰�˳�������
				ordf.m_orderData[record[select - 1]]["status"] = "0";
				// ����������Ϻ� ������д���ļ�
				ordf.updateOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "�����������������룡" << endl;
	}

	system("pause");
	system("cls");
}
// ��ʼ������
void Student::initVector()
{
	// ��ȡ������Ϣ,�������ڻ���������
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom comp;
	while (ifs >> comp.m_Comid&&ifs >> comp.m_MaxNum)
	{
		this->vCom.push_back(comp);
	}
	ifs.close();
}