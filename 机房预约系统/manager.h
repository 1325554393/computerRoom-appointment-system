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
	// 添加账号
	void addPerson();
	// 查看账号
	void showPerson();
	// 查看机房信息
	void showComputer();
	// 清空预约记录
	void cleanFile();

	// 添加账号-去重
	// 账号去除-读取账号所有信息，并储存在vector<>容器中
	// 故因先创建容器，并初始化容器
	// 初始化容器
	void initVector();
	// 学生和老师容器
	vector<Student> vStu;
	vector<Teacher> vTea;
	// 去重函数-id号去重， type是账号的类型
	bool checkRepeat(int id, int type);

	// 查看机房信息-添加容器
	vector<ComputerRoom> vCom;

	// 清空预约记录-判断是否确认清空
	bool checkClear();


private:

};

