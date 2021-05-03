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

	// ����ԤԼ��¼
	void updateOrder();

	// ��¼���� key---��¼�������� value---��¼�ľ�����Ϣ
	map < int, map<string, string> > m_orderData;

	// ��¼ԤԼ����
	int m_Size;
};