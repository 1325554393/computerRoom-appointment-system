#pragma once
#include "identity.h"
#include <iostream>
#include <string>
#include "student.h"
#include "orderFile.h"
#include <vector>
using namespace std;

class Teacher: public Identity
{
public:
	Teacher();
	Teacher(int empId, string name, string pwd);
	~Teacher();

	virtual void operMenu();
	// �鿴����ԤԼ
	void showAllOrder();
	// ���ԤԼ
	void validOrder();

	// ��ʦ�Ķ�������-ְ����
	int m_EmpId;

private:

};

