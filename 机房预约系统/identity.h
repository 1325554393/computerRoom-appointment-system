#pragma once
#include <iostream>
using namespace std;

/*因为要创建三个身份 ，但三个身份都含有登录名和密码，因此可创建一个身份的基类， 包含这两种信息
随后的三种身份都在在此基础上继承属性.
另外对于三种身份登录后，都有对应的菜单操作，故可创建虚函数接口，由子类改写*/

// 抽象基类
class Identity
{
public:
	// 纯虚函数-菜单接口-需由子类改写
	virtual void operMenu() = 0;

	string m_Name; // 用户名
	string m_Pwd; // 密码

};