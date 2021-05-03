#pragma once
#include <iostream>
#include "identity.h"
#include "computerRoom.h"
#include <string>
#include <vector>
#include <fstream>
#include "globalFile.h"
#include "orderFile.h"
using namespace std;

// ѧ���� 
class Student :public Identity
{
public:
	// Ĭ�Ϲ��캯��
	Student();
	// �вι���
	Student(int id, string name, string pwd);
	//����
	~Student();

	// �����ܺ���
	// �˵����� ����д�����еĴ��麯���������������������� �޷�ʵ��������
	virtual void operMenu();
	// ����ԤԼ
	void applyOrder();
	// �鿴�ҵ�ԤԼ
	void showMyOrder();
	// �鿴����ԤԼ
	void showAllOrder();
	// ȡ��ԤԼ
	void cancelOrder();

	// ѧ���Ķ�������-ѧ��
	int m_Id;

	// ����ԤԼ-��������
	vector<ComputerRoom> vCom;
	// ��ʼ������
	void initVector();

};