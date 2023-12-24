// Copyright (c) 2023, Свидич Н.А., ЮФУ ИКТИБ, Ктбо1-2
// 
// Дисциплина: Алгоритмизация и программирование
// Индивидуальное задание №1. Вариант 22.
// 
// Разработка программы, которая считывает настроечные параметры и формирует отчет по имеющимся данным в файлах. 
// Отчет записывается в текстовый файл. Число записей в каждом из описанных выше файлов произвольно.
// Отобрать все номера телефонов с заданной суммой баланса, которые в течение последней недели говорили каждый день не менее заданного количества минут.
// 
// Входные данные: Сумма баланса, количество минут разговора.
// Выходные данные: файл report.txt с записью полученных при выполнении поиска номеров телефона или выводом сообщения об их отсутствии.
// 
// Последнее обновление: 24.12.2023
// 

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable : 4996)
#define MAX_DATA_SIZE 50 // Макс размер для строк данных в структуре
#define MAX_LIST_SIZE 50 // Макс размер для динамического выделения памяти массивов
#define REPORT_FN "..\\report.txt"
#define PARAM_FN "..\\param.ini"
#define SERVICE_FN "..\\service.txt"

// Хранение данных о Записях Совершенных Услуг
struct complete_provides {
	char phone_number[16]; // Номер телефона
	unsigned int code; // Код услуги
	int date_day, date_mon, date_year; // Дата: день, мес, год. В отдельных переменных для доступа к отдельному сравнению дней
	unsigned int time; // Время услуги в минутах
	float phone_balance; // Баланс номера
};

// Функция сравнения времени с текущей датой. Работает корректно - наглядная доп проверка в функции file_complete_provides_read
int time_mir(complete_provides* provide) {

	// Определение сегодняшней даты
	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);
	int now_day = now->tm_mday, now_mon = now->tm_mon + 1, now_year = now->tm_year + 1900;

	int result = 0; // Доп переменная для определения совпадения

	// Проверка - было ли начало недели в прошлом месяце, и входит ли считываемая дата в диапозон недели
	if (now_day >= 8) {
		if (provide->date_day <= now_day && provide->date_day >= now_day - 7) {
			result = 1;
		}
		else result = 0;
	}
	else if (now_day < 8) {
		if (provide->date_mon + (now_day - provide->date_day) <= 7) {
			result = 1;
		}
		else result = 0;
	}

	return result;
}

// Функция считывания параметров из файла param.ini
void file_params_read(int search_balance, unsigned int search_time) {
	FILE* file_param = fopen(PARAM_FN, "r");

	// Переменные - буферы: строка файла, хранение строки первого параметра, хранение строки второго параметра
	char stroke[256], str_balance[256], str_time[256];

	int data = 1; // Счетчик строк - параметров, для корректного назначения значений

	if (file_param == NULL) perror("Opening param.ini file error");
	else {

		while (fgets(stroke, sizeof(stroke), file_param) != NULL) {

			// Если строка не является комментарием или заголовком, считывание строк - параметров
			if (stroke[0] != ';' && stroke[0] != '[' && stroke[0] == 's') {
				if (data == 1) strcpy(str_balance, stroke);
				if (data == 2) strcpy(str_time, stroke);
				data++;
			}

		}

	}

	// Заполнение из строк - параметров значений в программные переменные
	sscanf(str_balance, "search_phone_balance   = %i ", &search_balance);
	sscanf(str_time, "search_provide_time    = %u ", &search_time);

	printf("Balance for search: %d Time for search(min): %u\n", search_balance, search_time);
	fclose(file_param);
}

// Функция чтения данных из файла с информацией об услугах и запись в структуры. Работает корректно - функция printf выводит уже заполненные структуры из массива
int file_complete_provides_read(complete_provides* provide) {
	FILE* file = fopen(SERVICE_FN, "r");
	unsigned int id = 0; // Кол-во считанных данных, в дальнейшем используется как длина списка массива

	if (file == NULL) perror("Opening file for reading error");
	else {
		// Переменные - буферы
		char file_line[256], complete_provide_date[20]; 
		puts("Provides list:");
		while (fgets(file_line, sizeof(file_line), file) != NULL) {
			sscanf(file_line, "%[^,], %u, %[^,], %u, %f ", &provide[id].phone_number, &provide[id].code, complete_provide_date, &provide[id].time, &provide[id].phone_balance); // Чтение строки из файла
			sscanf(complete_provide_date, "%u.%u.%u", &provide[id].date_day, &provide[id].date_mon, &provide[id].date_year); // Разделение полученной строки с датой на день, мес, год
			provide[id].time = provide[id].time / 60; // Конвертация секунд в минуты

			printf("%s %i %i.%i.%i %i %.2f\n", provide[id].phone_number, provide[id].code, provide[id].date_day, provide[id].date_mon, provide[id].date_year, provide[id].time, provide[id].phone_balance);
			id++;
		}

	}

	fclose(file);
	return id;
}

// Функция поиска по заданным параметрам. Работает корректно - выводит номер, если семь совпадений, если хотя бы шесть - нет данных. Доработать - если день одинаковый
void search(complete_provides* provide, unsigned int complete_provides_cnt, int search_balance, unsigned int search_time) {
	
	FILE* output = fopen(REPORT_FN, "a");
	if (output == NULL) perror("Opening file output.txt for writing error");

	complete_provides* search_provides_buff = (complete_provides*)malloc(sizeof(complete_provides) * complete_provides_cnt); // Буфер для найденных значений
	int week_result_count = 0, result_cnt = 0, res = 0; // Кол-во записей в списках результатов

	// Если данные подходят под условия, заполняется массив - буфер, подсчет заполненных результатов (в дальнейшем - длина массива-буфера)
	for (int i = 0, k = 0; i <= complete_provides_cnt; i++) {
		if (provide[i].phone_balance >= search_balance && provide[i].time >= search_time && time_mir(&provide[i]) == 1) {
			search_provides_buff[k] = provide[i];
			k++;
			result_cnt++;
		}
	}

	// Поиск по списку подходящих под условия значений. Если найдено 7 одинаковых номеров за период в неделю - вывод номера
	for (int i = 0; i <= result_cnt; i++) {
		week_result_count = 0;

		for (int j = 0; j <= result_cnt; j++) {
			
			if ( strcmp(search_provides_buff[i].phone_number, search_provides_buff[i+j].phone_number) == 0) {
				week_result_count++;
			}

			if (week_result_count == 7) {
				printf("\nData found: %s", search_provides_buff[i].phone_number);
				fprintf(output, "Data found: %s\n", search_provides_buff[i].phone_number);
				
				res++;
				break;
			}

		}

	}

	// Если ни один номер не найден, вывод об отсутствии данных
	if (res == 0) { 
		puts("\nData not found"); 
		fputs("Data not found", output);
	}


	free(search_provides_buff);
	fclose(output);
}


int main() {
	FILE* output = fopen(REPORT_FN, "w"); // В функции поиска, при открытии файла используется режим добавления строк, при котором сохраняются записи с прошлого запуска программы
	fclose(output); // Для избежания этого, в начале программы файл открывается в режиме перезаписи, чтобы стереть прошлые данные

	complete_provides* complete_provides_list = (complete_provides*)malloc(sizeof(complete_provides) * MAX_LIST_SIZE); // Массив структур с данными об услугах
	unsigned int complete_provides_cnt = 0; // Кол-во занесенных записей в массив структур
	float search_balance = 150; // Значение баланса для поиска по списку
	unsigned int search_time = 1; // Значение для поиска, время исп услуги в мин

	file_params_read(search_balance, search_time); // Считывание параметров из файла param.ini значений для поиска
	complete_provides_cnt = file_complete_provides_read(complete_provides_list) - 1; // Считывание данных об услугах из файла info.txt в массив структур

	search(complete_provides_list, complete_provides_cnt, search_balance, search_time); // Вызов функции поиска по массиву записей с считанными параметрами

	free(complete_provides_list); // Освобождение памяти занимаемой массивом

	return 0;
}