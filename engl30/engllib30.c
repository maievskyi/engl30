//
//
//
//
//


#define _CRT_SECURE_NO_WARNINGS  //   ?? подробнее об предупреждениях ??

#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include"engl30.h"  //






////////////============   a-я изменения строки - имени файла   ====== ВНУТРИ СОЗД ДИН ПАМ ! ?? ///////
char* rename2(const char* poldname, char *paddstring, int del) // ф -я укорачивает имя poldname.ext
															   //на del и  добавляет paddstring віделяет дин пам нужного разм и возвл указ на него
{
	//дин стр oldname укорачивается на длинну del , дописывая стр pletteadd
	//и всё это возвращается в указателе на строку - pnewname
	char *ptempstrstr = (char*)malloc(strlen(poldname) + strlen(paddstring));
	// память для нов стр
	//printf(" ########  inside of rename2(); #########\n ");    // temp
	memset(ptempstrstr, '\0', (strlen(poldname) + strlen(paddstring)));			// заполнение \0 
	strncpy(ptempstrstr, poldname, (strlen(poldname) - del));	// копируем без .ext
																//printf(" ~~~внутр перем ptempstrstr, = ( %s )   ~~~\n", ptempstrstr );    // temp
	strcat(ptempstrstr, paddstring);  // добавл строку
	printf(" ~~~внутри rename2() вн перем ptempstrstr,= ( %s ) ~~~\n", ptempstrstr);  // temp
	return (ptempstrstr);
}; //    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END rename2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
   //    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END rename2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
