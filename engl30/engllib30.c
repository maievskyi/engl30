//
//
//
//
//


#define _CRT_SECURE_NO_WARNINGS  //   ?? ��������� �� ��������������� ??

#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include"engl30.h"  //






////////////============   a-� ��������� ������ - ����� �����   ====== ������ ���� ��� ��� ! ?? ///////
char* rename2(const char* poldname, char *paddstring, int del) // � -� ����������� ��� poldname.ext
															   //�� del �  ��������� paddstring ������� ��� ��� ������� ���� � ����� ���� �� ����
{
	//��� ��� oldname ������������� �� ������ del , ��������� ��� pletteadd
	//� �� ��� ������������ � ��������� �� ������ - pnewname
	char *ptempstrstr = (char*)malloc(strlen(poldname) + strlen(paddstring));
	// ������ ��� ��� ���
	//printf(" ########  inside of rename2(); #########\n ");    // temp
	memset(ptempstrstr, '\0', (strlen(poldname) + strlen(paddstring)));			// ���������� \0 
	strncpy(ptempstrstr, poldname, (strlen(poldname) - del));	// �������� ��� .ext
																//printf(" ~~~����� ����� ptempstrstr, = ( %s )   ~~~\n", ptempstrstr );    // temp
	strcat(ptempstrstr, paddstring);  // ������ ������
	printf(" ~~~������ rename2() �� ����� ptempstrstr,= ( %s ) ~~~\n", ptempstrstr);  // temp
	return (ptempstrstr);
}; //    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END rename2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
   //    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END rename2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
