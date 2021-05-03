#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include "globalFile.h"
using namespace std;

class OrderFile
{
public:
	OrderFile();

	// 更新预约记录
	void updateOrder();

	// 记录容器 key---记录的条数， value---记录的具体信息
	map < int, map<string, string> > m_orderData;

	// 记录预约条数
	int m_Size;
};