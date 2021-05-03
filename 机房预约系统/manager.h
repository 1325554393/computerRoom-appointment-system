#pragma once
#include "identity.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include "computerRoom.h"
using namespace std;

class Manager:public Identity
{
public:
	Manager();
	Manager(string name, string pwd);
	~Manager();

	virtual void operMenu();
	// ����˺�
	void addPerson();
	// �鿴�˺�
	void showPerson();
	// �鿴������Ϣ
	void showComputer();
	// ���ԤԼ��¼
	void cleanFile();

	// ����˺�-ȥ��
	// �˺�ȥ��-��ȡ�˺�������Ϣ����������vector<>������
	// �����ȴ�������������ʼ������
	// ��ʼ������
	void initVector();
	// ѧ������ʦ����
	vector<Student> vStu;
	vector<Teacher> vTea;
	// ȥ�غ���-id��ȥ�أ� type���˺ŵ�����
	bool checkRepeat(int id, int type);

	// �鿴������Ϣ-�������
	vector<ComputerRoom> vCom;

	// ���ԤԼ��¼-�ж��Ƿ�ȷ�����
	bool checkClear();


private:

};

