﻿//25/05/23 первый  вариант 
//09/06/23 Открываем из INI базу слов с переводом и корректируем перевод
//
//
//
//
//
//
//
// Создаём копию в GitHub



#define _CRT_SECURE_NO_WARNINGS  //   ?? подробнее об предупреждениях ??
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include"engl30.h"  //



FILE *pFini;	//---> указатель на структ. файл в котором сохранять файлов fini.dat

FILE *pFcommon;	//---> указатель на структ. ф в котором накоплена общая база слов с перев
FILE *pFsort;	//---> указатель на структ. ф в котором сохранена алф сорт базу слов
FILE *pFfreqsort;//---> указ на  ф в котор сохранена частотно-сорт базу слов


struct inidat *pcommon;	//--->указ на ДИН пам общей базы слов с перев
struct inidat *psettings;	//--->указ на ДИН пам базы ini имён и настроек прог-мы

struct word *pmemsortword = NULL;  //--> указ на д пам стрктур с отсортированными словами


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       main     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
int main(int argc, const char ** argv, const char** env)
{

	system("chcp 1251 > nul");
	errno_t err;			//  переменная (int?) для вывода ошибок ? внутр переменная (int?)

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    1    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//_ 1 a __ открытие файла общей базы слов, или при отсутствии - созд новой
	err = fopen_s(&pFcommon, "commondictionary.dat", "r+b");	 // открывается ли на ЧТЕНИЕ с дозаписью
	if (err)	// НЕТ  СТАРОГО файла общей базы слов "r+b" = нет. Делаем новый = "w+b"							
	{			// (!!! только "r" в VS чтото не получилось)
		perror("commondictionary.dat");
		puts("\n !!! НЕ найден файл commondictionary.dat \n  нажмите 'y или n'\n чтобы создать новый\n");
		if ('y' == _getch(stdin))//   ============
		{
			// значит открывается НОВЫЙ commondictionary.dat "w+b" на ЗАПИСЬ-ЧТЕНИЕ
			err = fopen_s(&pFcommon, "commondictionary.dat", "w+b");
			if (err)	//ошибка выход почему-то  НЕ СОЗДАЛСЯ НОВЫЙ commondictionary.dat
			{
				puts("\n !!! почемуто не создался новый файл commondictionary.dat \n");
				perror("commondictionary.dat");
				//free(psettings);				//освоб памяти
				system("pause");
				exit(1);					// выход урок сорвался
			}
			puts("\n  открывается НОВЫЙ commondictionary.dat \"w + b\" на ЗАПИСЬ-ЧТЕНИЕ \n");
			
		}
		else
		{
			exit(1);
		} // end else 'y' == _getch(stdin)
	} // end if (err) НЕТ  СТАРОГО файла общей базы слов "r+b" = нет. Делаем новый = "w+b"	
	puts("\n  открыт поток pFcommon к ф-лу  commondictionary.dat  \n");
	// < теперь по указателю pFcommon открыт поток к файлу commondictionary.dat - база слов с переводом


//_ 1 b __ есть ли ф fini.dat  ==============================================================

//_ 1 b __ открытие=проверка сущ-вания стар INI ФАЙЛА пользов настр "fini.dat"=============		
	err = fopen_s(&pFini, "fini.dat", "r+b");	 // открывается ли на ЧТЕНИЕ с дозаписью
	if (err)	// НЕТ  СТАРОГО fini.dat "r+b" = нет. Делаем новый = "w+b"							
	{			// (!!! только "r" в VS чтото не получилось)
		perror("fini.dat");
		puts("\n !!! НЕ НАЙДЕН ini файл пользователя \n создайте его сортировкой текста \n нажмите ENYKEY чтобы выйти\n");
		system("pause");
		//free(psettings->ininamenosortf);
		//free(psettings);//оcвоб пам с настройками из ф ini
		exit(1);

		/*
		
		*/
	} // end if "нет  стар fini.dat r+b" = нет. Сделан новый ,,,,,,,,,,,,,,,,,,,,,,,,
	else // значит существует и открылся fini.dat по указат pFini
	{
		// > создание  дин памяти psettings
		psettings = (struct inidat*)malloc(sizeof(struct inidat)); //созд ДИН пам под стркт
		if (psettings == NULL)printf("Не выделена память ini настройки программы \n");
		else printf("  Выделена дин пам psettings = %d Bytes \n\
 под ini структуру-настройки программы \n", sizeof(struct inidat));	// debug
		// считываем из pFini в дин пам - psettings всех настроек
		size_t result = fread(psettings, sizeof(struct inidat), QUANTITYNAME, pFini);
		// ввод в psettings имеющихся СТАРЫХ настроек и имени уже разб-го т-та - для открытия ф баз 
		puts("\n Открылись и перенесены в psettings Начальн. СТАРЫЕ  настр-ки (чт с дозап ini ф) \n");
		// закрыть ф поток в который запис ini настройки 
		system("pause");
		fclose(pFini);	// закрытие fini.dat 
	}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   2   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*  _2_ во время обьединения в алф базу слов из txt сравнивается и переносятся перевод слов из общей,
если нет слова мперевода открыв редактор и вносится перевод с одновременным перенесением в общую базу
и в частотную базу текста, если есть перевод то в зависимости от доп выбора перевод редактируется
во всех базах или переносится без редакции. Затем фиксируются изменения в файлах */

//_ 2 __ Обьединение слов из текста с общей базой слов в паяти по указателю *pcommon

//_ 2 a __открываем и затем считываем в д пам АЛФ сорт файл
	err = fopen_s(&pFsort, psettings->ininamealphsortf, "r+b");//XXX_alphsort.dat сохр в ф-л "fini.dat"
	if (err) //   a)
	{
		puts("\n Ошибка! \n Неудача отытия ранее созданного ф-ла алфавитно-сортированных слов \n");
		system("pause");
		exit(1);
	}
	else   //	b) Удачно откр-ся и далее считываем в д пам алф сорт файл
	{

		// Удачно откр-ся и далее считываем в д пам алф сорт файл текста
		long fileSize = 0;	////~~~~~~~  определяем РАЗМЕР входн ***.txt файла в байтах  -----	 
		fseek(pFsort, 0, SEEK_END);// уст-ем текущ поз в смещ на 0 относ конца ф-ла
		fileSize = ftell(pFsort); //в txtSize = ПОЛУЧАЕМ РАЗМЕР В БАЙТАХ
		fseek(pFsort, 0, SEEK_SET);	// перевести текущую поз на начало файла

		printf("Размер д пам для алфав-сортированной базы из ф-ла = %d Bytes \n", fileSize);
			//выделяем эту д память под алф-сорт
		pmemsortword = (byte*)malloc(fileSize);
		if (pmemsortword == NULL)
		{
			printf("Не выделенна память под pmemsortword \n");
			system("pause");
			exit(1);
		}

		size_t result = fread(pmemsortword, sizeof(byte), fileSize, pFsort);
		// алф сортиров-й массив слов считан повторн из ф в д п pmemsortword 
		puts("\n Алфавитно сортированный файл считан номально! \n  \n");
		fclose(pFsort);
	}     //	end Удачно откр-ся, считался в д пам и закрылся алф сорт файл текста

//_ 2 b __ в увел-ю на число слов текста память переносим common базу для дальн редакт-ния
	



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   3   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/* _3_  Начинается урок по базе из файла */



	free(psettings);				//освоб памяти
	free(pmemsortword);
	fclose(pFcommon);//закрытие потока
	system("pause");
}  //end main