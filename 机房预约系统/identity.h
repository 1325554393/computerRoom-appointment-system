#pragma once
#include <iostream>
using namespace std;

/*��ΪҪ����������� ����������ݶ����е�¼�������룬��˿ɴ���һ����ݵĻ��࣬ ������������Ϣ
����������ݶ����ڴ˻����ϼ̳�����.
�������������ݵ�¼�󣬶��ж�Ӧ�Ĳ˵��������ʿɴ����麯���ӿڣ��������д*/

// �������
class Identity
{
public:
	// ���麯��-�˵��ӿ�-���������д
	virtual void operMenu() = 0;

	string m_Name; // �û���
	string m_Pwd; // ����

};