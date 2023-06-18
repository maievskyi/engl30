#pragma once

#define TEXTIN "text00.txt"

#define QUANTITYNAME 1 // кол-во записей элементов стр-тур в массиве имён ф-в программы

#define EN1 256 //размер имени файла уже созданного с структурами word
#define EN 32 //размер англ текста (одного слова) в структ word
#define RU 32 //размер рус текста в структ word


char* rename2(const char* poldname, char *paddstring, int del); // ф -я укорачивает имя poldname.ext
	//на del и  добавляет paddstring віделяет дин пам нужного разм и возвл указ на него
//............................................................................................
struct inidat       // стр для хранения польз настроек имён файлов и др
{				//будут и другие поля;
	int idname;
	int sorttype; //выбор тип сортировки 1-алф(по умолч) 2-частот
	char name[EN1];    //имя файла
	char ininamenosortf[EN1];	//имя файла с несортрованн структ
	char ininamealphsortf[EN1];		//имя файла с алфавитно-сорт. структ
	char ininameafreqsortf[EN1];		//имя файла с частотно-сорт. структ
	int inicountsepword;//копия общего количества countnosort отсепарированных слов в тексте
	int inicountnumword;//копия общего кол отсеп слов countnumword без повторения, в тексте
						//char namepath[EN1];	// c полным путём
						//int number;  // размер файла
						//char namehelp[EN1]; // пояснения к файлу
						//int inicountnumword;//--->копия в ini файле числа  счетч слов
};
//.............................................................................................
struct word       // стр для хранения слов с переводом и др в
{
	int id;  // алфавитная id нумерация
	int repeat_id;	// нумерация по повторениям в тексте
	int random_id;	// произвольная нумерация в тексте
	int temp_id;	//
	int temp2_id;	//

	int repeat;	// количество повторений слова в тексте

	int typesort; // тип сортировки (алфав = 0, частотн = 1)
				  //char rait;  // рейтинг
				  //будут и другие поля;
	char en[EN];    //массив строчный - размером из #define
	char ru[RU];	// то же
	char tempchar; // отладка временно для выравн при просм  F3
	int tempint;
};