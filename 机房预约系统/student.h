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

// 学生类 
class Student :public Identity
{
public:
	// 默认构造函数
	Student();
	// 有参构造
	Student(int id, string name, string pwd);
	//析构
	~Student();

	// 各功能函数
	// 菜单函数 需重写基类中的纯虚函数，否则子类依旧是虚类 无法实例化对象
	virtual void operMenu();
	// 申请预约
	void applyOrder();
	// 查看我的预约
	void showMyOrder();
	// 查看所有预约
	void showAllOrder();
	// 取消预约
	void cancelOrder();

	// 学生的独特属性-学号
	int m_Id;

	// 申请预约-机房容器
	vector<ComputerRoom> vCom;
	// 初始化容器
	void initVector();

};