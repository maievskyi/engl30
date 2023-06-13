//25/05/23 первый  вариант 
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



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       main     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
int main(int argc, const char ** argv, const char** env)
{

	system("chcp 1251 > nul");
	errno_t err;			//  переменная (int?) для вывода ошибок ? внутр переменная (int?)


//________ открытие файла общей базы слов, или при отсутствии - созд новой
	err = fopen_s(&pFcommon, "commondictionary.dat", "r+b");	 // открывается ли на ЧТЕНИЕ с дозаписью
	if (err)	// НЕТ  СТАРОГО файла общей базы слов "r+b" = нет. Делаем новый = "w+b"							
	{			// (!!! только "r" в VS чтото не получилось)
		perror("commondictionary.dat");
		puts("\n !!! НЕ найден файл commondictionary.dat \n  нажмите 'y или n'\n чтобы создать новый\n");
		//system("pause");
		if ('n' == _getch(stdin))//   ============
		{
			exit(1);
		}
		else
		{
			// значит открывается НОВЫЙ INI commondictionary.dat "w+b" на ЗАПИСЬ-ЧТЕНИЕ
			err = fopen_s(&pFcommon, "commondictionary.dat", "w+b");
			if (err)	//ошибка выхол почему-то  НЕ СОЗДАЛСЯ НОВЫЙ fini.dat
			{
				puts("\n !!! почемуто не создался новый commondictionary.dat \n");
				perror("commondictionary.dat");
				//free(psettings);				//освоб памяти
				system("pause");
				exit(1);					// выход урок сорвался
			}
			puts("\n  открывается НОВЫЙ commondictionary.datcommondictionary.dat \"w + b\" на ЗАПИСЬ-ЧТЕНИЕ \n");

		} // end else
	} // end if (err)
//__________________________________________________________________________________________
		/*
		//// значит открывается НОВЫЙ INI fini.dat "w+b" на ЗАПИСЬ-ЧТЕНИЕ
		err = fopen_s(&pFini, "fini.dat", "w+b");
		if (err)	//ошибка выхол почему-то  НЕ СОЗДАЛСЯ НОВЫЙ fini.dat
		{
		puts("\n !!! почемуто не создался новый ini файл пользователя \n");
		perror("fini.dat");
		free(psettings);				//освоб памяти
		system("pause");
		exit(1);					// выход урок сорвался
		}
		else
		{	// открылся НОВЫЙ fini.dat на ЗАПИСЬ-ЧТЕНИЕ
		// (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^)
		// ПОПОЗЖЕ тут дописать в дин пам psettings настр по умолчанию !!! ^^^^^^
		//psettings->sorttype = 1; // по умолч алфав сортировка
		//strncpy(psettings->ininamenosortf, TEXTIN"_nosort.dat", EN1); // имя несорт ф
		//strncpy(psettings->ininamealphsortf, TEXTIN"_alphsort.dat", EN1);// имя алфав сорт ф
		//strncpy(psettings->ininameafreqsortf, TEXTIN"_freqalphsort.dat", EN1);//имя част-алфав ф
		//psettings->inicountsepword = 0; // по умолч отсепарировано
		//psettings->inicountnumword = 0; // по умолч  отсортированноо с уменьшением еол слов
		//запись  стандартн по умлч настроек ИЗ ДИН ПАМЯТИ ?pmeminidat? в ф fini.dat  ======
		size_t result = fwrite(psettings, sizeof(struct inidat), QUANTITYNAME, pFini);
		//puts("\n +++  создался  НОВЫЙ ini файл пользователя со стнд настр \n");	//debug
		puts("\n Записан из Д ПАМ на HDD Новый стандартный файл пользователя \
		с стнд настр\"fini.dat\" \n");

		fclose(pFini);	// закрыть ф-й поток в который записаны настройки ini по умолчанию
		//puts("\n +++  создался  НОВЫЙ ini файл пользователя со стнд настр \n");	//debug
		}
//____________________________________________________________________________







	//1)создание  дин памяти psettings
	psettings = (struct inidat*)malloc(sizeof(struct inidat)); //созд ДИН пам под стркт
	if (psettings == NULL)printf("Не выделена память ini настройки программы \n");
	else printf("  Выделена дин пам psettings = %d Bytes \n\
 под ini структуру-настройки программы \n", sizeof(struct inidat));	// debug

	//присвоить имя динамической струтуре = struct inidat --- settings  ---
	//struct inidat settings = *psettings;


	memset(psettings, '\0', sizeof(struct inidat)); //  обнуление динам структуры INI
	/*
	//СТАНДАРТНЫЕ настройки (из шаблона) динам структуры INI ===============================
	psettings->sorttype = 1; // по умолч алфав сортировка
	strncpy(psettings->name, TEXTIN, EN1); // имя  ф
	strncpy(psettings->ininamenosortf, rename2(TEXTIN, "_nosort.dat", 4), EN1); // имя несорт ф
	strncpy(psettings->ininamealphsortf, rename2(TEXTIN, "_alphsort.dat", 4), EN1); // имя алфав сорт ф
	strncpy(psettings->ininameafreqsortf, rename2(TEXTIN, "_freqalphsort.dat", 4), EN1); //имя част-алфав ф
	psettings->inicountsepword = 0; // копия общего кол countnosort отсепарир-х слов в тексте
	psettings->inicountnumword = 0; // копия общего кол countnosort отсепарир-х слов в тексте
	*/
	//_________________________________________________________________________________________						


	//2) есть ли ф fini.dat  ==============================================================

	//2) открытие=проверка сущ-вания стар INI ФАЙЛА пользов настр "fini.dat"=============		
	err = fopen_s(&pFini, "fini.dat", "r+b");	 // открывается ли на ЧТЕНИЕ с дозаписью
	if (err)	// НЕТ  СТАРОГО fini.dat "r+b" = нет. Делаем новый = "w+b"							
	{			// (!!! только "r" в VS чтото не получилось)
		perror("fini.dat");
		puts("\n !!! НЕ найден ini файл пользователя \n создайте его сортировкой текста \n нажмите ENYKEY чтобы выйти\n");
		system("pause");
		//free(psettings->ininamenosortf);
		free(psettings);//оcвоб пам с настройками из ф ini
		exit(1);
		/*
		//// значит открывается НОВЫЙ INI fini.dat "w+b" на ЗАПИСЬ-ЧТЕНИЕ
		err = fopen_s(&pFini, "fini.dat", "w+b");
		if (err)	//ошибка выхол почему-то  НЕ СОЗДАЛСЯ НОВЫЙ fini.dat 								
		{
			puts("\n !!! почемуто не создался новый ini файл пользователя \n");
			perror("fini.dat");
			free(psettings);				//освоб памяти
			system("pause");
			exit(1);					// выход урок сорвался
		}
		else
		{	// открылся НОВЫЙ fini.dat на ЗАПИСЬ-ЧТЕНИЕ
			// (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^)
			// ПОПОЗЖЕ тут дописать в дин пам psettings настр по умолчанию !!! ^^^^^^
			//psettings->sorttype = 1; // по умолч алфав сортировка
			//strncpy(psettings->ininamenosortf, TEXTIN"_nosort.dat", EN1); // имя несорт ф
			//strncpy(psettings->ininamealphsortf, TEXTIN"_alphsort.dat", EN1);// имя алфав сорт ф
			//strncpy(psettings->ininameafreqsortf, TEXTIN"_freqalphsort.dat", EN1);//имя част-алфав ф
			//psettings->inicountsepword = 0; // по умолч отсепарировано
			//psettings->inicountnumword = 0; // по умолч  отсортированноо с уменьшением еол слов
			//запись  стандартн по умлч настроек ИЗ ДИН ПАМЯТИ ?pmeminidat? в ф fini.dat  ======		
			size_t result = fwrite(psettings, sizeof(struct inidat), QUANTITYNAME, pFini);
			//puts("\n +++  создался  НОВЫЙ ini файл пользователя со стнд настр \n");	//debug			
			puts("\n Записан из Д ПАМ на HDD Новый стандартный файл пользователя \
с стнд настр\"fini.dat\" \n");

			fclose(pFini);	// закрыть ф-й поток в который записаны настройки ini по умолчанию
							//puts("\n +++  создался  НОВЫЙ ini файл пользователя со стнд настр \n");	//debug			
		}
		

		//3) контрольно ПЕРЕОТКРЫВАЕТСЯ .INI на чтен с дозаписью
		err = fopen_s(&pFini, "fini.dat", "r+b");// ПЕРЕОТКРЫВАЕТСЯ ли на чте с дозаписью
		if (err)	// значит не открылся fini.dat  - и выход								
		{
			perror("fini.dat");
			puts("\n !!!!! НЕ переоткрылся на чт с дозап ini файл пользователя   \n");
			system("pause");
			exit(1);					//НЕ переоткрылся на чт с дозап ini файл
		}
		// получилось создать новый закрыть и по новой открыть "fini.dat"
		else
		{
			puts("\n Открылся на чт с дозап нов fini.dat файл польз-ля с стандартн настр  \n");
		}
		system("pause");
		*/
	} // end if "нет  стар fini.dat r+b" = нет. Сделан новый ,,,,,,,,,,,,,,,,,,,,,,,,
	else // значит существует и открылся fini.dat по указат pFini
	{
		// )создание  дин памяти psettings
		psettings = (struct inidat*)malloc(sizeof(struct inidat)); //созд ДИН пам под стркт
		if (psettings == NULL)printf("Не выделена память ini настройки программы \n");
		else printf("  Выделена дин пам psettings = %d Bytes \n\
 под ini структуру-настройки программы \n", sizeof(struct inidat));	// debug
		// считываем из pFini в дин пам - psettings всех настроек
		size_t result = fread(psettings, sizeof(struct inidat), QUANTITYNAME, pFini);
		// ввод в psettings имеющихся СТАРЫХ настроек и имени уже разб-го т-та - для открытия ф баз 
		puts("\n Открылись и перенесены в psettings Начальные СТАРЫЕ  настр-ки (чт с дозап ini ф) \n");
		// закрыть ф поток в который запис ini настройки 
		system("pause");
		fclose(pFini);	// закрытие fini.dat 

	}


	fclose(pFcommon);//оcвоб пам с настройками из ф ini
	system("pause");
}  //end main