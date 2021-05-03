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
	// 查看所有预约
	void showAllOrder();
	// 审核预约
	void validOrder();

	// 老师的独特属性-职工号
	int m_EmpId;

private:

};

