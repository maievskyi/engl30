#pragma once

#define TEXTIN "text00.txt"

#define QUANTITYNAME 1 // ���-�� ������� ��������� ���-��� � ������� ��� �-� ���������

#define EN1 256 //������ ����� ����� ��� ���������� � ����������� word
#define EN 32 //������ ���� ������ (������ �����) � ������ word
#define RU 32 //������ ��� ������ � ������ word


char* rename2(const char* poldname, char *paddstring, int del); // � -� ����������� ��� poldname.ext
	//�� del �  ��������� paddstring ������� ��� ��� ������� ���� � ����� ���� �� ����
//............................................................................................
struct inidat       // ��� ��� �������� ����� �������� ��� ������ � ��
{				//����� � ������ ����;
	int idname;
	int sorttype; //����� ��� ���������� 1-���(�� �����) 2-������
	char name[EN1];    //��� �����
	char ininamenosortf[EN1];	//��� ����� � ������������ ������
	char ininamealphsortf[EN1];		//��� ����� � ���������-����. ������
	char ininameafreqsortf[EN1];		//��� ����� � ��������-����. ������
	int inicountsepword;//����� ������ ���������� countnosort ���������������� ���� � ������
	int inicountnumword;//����� ������ ��� ����� ���� countnumword ��� ����������, � ������
						//char namepath[EN1];	// c ������ ����
						//int number;  // ������ �����
						//char namehelp[EN1]; // ��������� � �����
						//int inicountnumword;//--->����� � ini ����� �����  ����� ����
};
//.............................................................................................
struct word       // ��� ��� �������� ���� � ��������� � �� �
{
	int id;  // ���������� id ���������
	int repeat_id;	// ��������� �� ����������� � ������
	int random_id;	// ������������ ��������� � ������
	int temp_id;	//
	int temp2_id;	//

	int repeat;	// ���������� ���������� ����� � ������

	int typesort; // ��� ���������� (����� = 0, ������� = 1)
				  //char rait;  // �������
				  //����� � ������ ����;
	char en[EN];    //������ �������� - �������� �� #define
	char ru[RU];	// �� ��
	char tempchar; // ������� �������� ��� ������ ��� �����  F3
	int tempint;
};