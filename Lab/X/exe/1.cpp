// Copyright (c) 2023, Свидич Н.А., ЮФУ ИКТИБ, Ктбо1-2
// 
// АиП Лабораторная работа №5. Вариант № 2. Работа со структурами.
// 
// Последнее обновление: 22.12.2023

#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable : 4996)
#define MAX_INFO_SIZE 20 // Макс размер строки данных в структуре
#define MAX_LIST_CUSTOMERS_SIZE 20 // Макс размер списка покупателей
// ||

// Описание структуры хранения данных
struct customer {
	char famil[MAX_INFO_SIZE]; // Фамилия
	char name[MAX_INFO_SIZE]; // Имя
	char otch[MAX_INFO_SIZE]; // Отчетсво
	char city[MAX_INFO_SIZE]; // Город
	char street[MAX_INFO_SIZE]; // Улица
	unsigned int house_num; // Дом
	unsigned int flat_num; // Квартира
	unsigned int credit_card; // Кредтка
	unsigned int code_shop; // Код покупки
};

// Вывод пунктов меню функций
int menu_func() {
	int choise;
	puts("\nМеню функций: ");
	puts("1. Записать нового пользователя \n2. Поиск пользователя \n3. Сортировка массива по параметру \n4. Вывод списка пользователей в консоль\n5. Вывод списка пользователей в файл \n6. Очистка данных \n7. Выход из программы");
	puts("Введите номер функции: ");
	scanf("%i", &choise);
	return choise;
}

// Функция записи новой структуры. Работает корректно, проверено путем записи в файл
int record_struct(customer* customer, unsigned id) {
	FILE* input = fopen("..\\data.txt", "a");
	int new_count;

	puts("Кол-во новых клиентов для записи: ");
	scanf("%i", &new_count);

	if (input == NULL) perror("Ошибка открытия файла data.txt для записи и хранения данных о покупателях");
	else {
		for (int i = 0; i < new_count; i++) {
			puts("Ввод нового покупателя: ");
			
			puts("Фамилия: ");
			scanf("%s", &customer[id + i].famil);
			puts("Имя: ");
			scanf("%s", &customer[id + i].name);
			puts("Отчество: ");
			scanf("%s", &customer[id + i].otch);
			puts("Город: ");
			scanf("%s", &customer[id + i].city);
			puts("Улица: ");
			scanf("%s", &customer[id + i].street);
			puts("Номер дома: ");
			scanf("%u", &customer[id + i].house_num);
			puts("Квартира: ");
			scanf("%u", &customer[id + i].flat_num);
			puts("Кредитная карта: ");
			scanf("%u", &customer[id + i].credit_card);
			puts("Код покупки: ");
			scanf("%u", &customer[id + i].code_shop);

			// Запись покупателя в файл исходных данных, чтобы не терять массив при новом запуске программы (используется каждый раз, после завершения выбранной в меню функции)
			fprintf(input, "%s %s %s %s %s %u %u %u %u \n",
				customer[id + i].famil, customer[id + i].name, customer[id + i].otch, customer[id + i].city, customer[id + i].street,
				customer[id + i].house_num, customer[id + i].flat_num, customer[id + i].credit_card, customer[id + i].code_shop);

			puts("Ввод завершен.\n");
		}
	}

	fclose(input);
	return id;
}

// Чтение уже существующих данных. Работает, проверено выводом кол-ва сущ записей при новом запуске программы
int read_data(customer* customr) {
	FILE* output = fopen("..\\data.txt", "r");
	unsigned count = 0;
	if (output == NULL) perror("Ошибка открытия файла data.txt для записи информации о покупателях в структуры");
	else {

		char stroke[256];
		int i = 0;

		while (fgets(stroke, sizeof(stroke), output) != NULL) {
			sscanf(stroke, "%s %s %s %s %s %u %u %u %u \n", &customr[i].famil, &customr[i].name, &customr[i].otch, &customr[i].city, &customr[i].street, &customr[i].house_num, &customr[i].flat_num, &customr[i].credit_card, &customr[i].code_shop);
			count++;
			i++;
		}

	}
	if (count == 0) puts("Сейчас данных о покупателях нет\n");

	fclose(output);
	return count;
}

// Функция вывода структур в консоль. Работает, проверено на практике - есть вывод
void print(customer* customr, int count) {

	if (customr == NULL) printf("Нет покупателей");
	else {
		puts("\n Данные о покупателях: \n");
		for (int i = 0; i < count; i++) {
			printf("%s \t %s \t %s \t %s \t %s \t %d \t %d \t %d \t %d \n", &customr[i].famil, &customr[i].name, &customr[i].otch, &customr[i].city, &customr[i].street, customr[i].house_num, customr[i].flat_num, customr[i].credit_card, customr[i].code_shop);
		}
	}

}

// Функция вывода структур в файл. Работает, проверено путем записи в файл
void output_file(customer* customer, unsigned count) {
	FILE* file = fopen("..\\output.txt", "w");

	if (file == NULL) perror("Ошибка открытия файла");
	else {

		if (customer == NULL) fprintf(file, "Нет покупателей");
		else {
			for (int i = 0; i < count; i++) {
				fprintf(file, "%s\t%s\t%s\t%s\t%s\t%u\t%u\t%u\t%u \n", customer[i].famil, customer[i].name, customer[i].otch, customer[i].city, customer[i].street, customer[i].house_num, customer[i].flat_num, customer[i].credit_card, customer[i].code_shop);
			}

			puts("Вывод завершен.\n");
		}
	}

	fclose(file);
}

// Функция вывода выбора параметров структуры
unsigned int menu_param() {
	unsigned int choise;
	puts("Список параметров: ");
	puts("1.фамилия \n2.имя \n3.отчество \n4.город \n5.улица \n6.номер дома \n7.номер квартиры \n8.номер кредитной карточки \n9.код покупки");
	puts("Введите номер нужного параметра: ");
	do {
		scanf("%u", &choise);
		printf("Выбрано: %u\n", choise);
	} while (choise < 1 || choise > 9);
	return choise;
}

// Функция поиска по значению параметра. Работает, проверено на практике - есть вывод
void search(customer* customer, int count) {
	char s_goal[MAX_INFO_SIZE]; // Доп переменная для сравнения по строкам
	unsigned int int_goal = 0, param, res; // Для числовых

	puts("Введите параметр для поиска: ");
	param = menu_param();
	puts("Введите значение параметра для поиска: ");
	// По числу параметра определяем, сравнивать числа или строки
	if (param >= 6) 
		scanf("%s", &int_goal);
	else scanf("%s", &s_goal);

	// проход по массиву данных
	for (int i = 0; i <= count; i++) {
		// Если хотя бы совпадение в параметре, вывод пользователя
		res = 0;
			switch (param) {
			case 1: if (strcmp(customer[i].famil, s_goal) == 0) res = 1;
				break;
			case 2: if (strcmp(customer[i].name, s_goal) == 0) res = 1;
				break;
			case 3:  if (strcmp(customer[i].otch, s_goal) == 0) res = 1;
				break;
			case 4: if (strcmp(customer[i].city, s_goal) == 0) res = 1;
				break;
			case 5: if (strcmp(customer[i].street, s_goal) == 0) res = 1;
				break;
			case 6: if (customer[i].house_num == int_goal) res = 1;
				break;
			case 7: if (customer[i].flat_num == int_goal) res = 1;
				break;
			case 8: if (customer[i].credit_card == int_goal) res = 1;
				break;
			case 9:if (customer[i].code_shop == int_goal) res = 1;
				break;
			default: break;
			}
			if (res == 1) printf("Найдено: %s\t%s\t%s\t%s\t%s\t%u\t%u\t%u\t%u \n", 
				customer[i].famil, customer[i].name, customer[i].otch, customer[i].city, customer[i].street, customer[i].house_num, customer[i].flat_num, customer[i].credit_card, customer[i].code_shop);
	}
	if (res == 0) puts("Совпадений не найдено");
}

// Функции для указания в qsort, отдельно по параметрам для возможности выбора
int name_cmp(const void* a, const void* b) {
	return strcmp( ((customer*)a)->name, ((customer*)b)->name);
}

int famil_cmp(const void* a, const void* b) {
	return strcmp( ((customer*)a)->famil, ((customer*)b)->famil);
}

int otch_cmp(const void* a, const void* b) {
	return strcmp(((customer*)a)->otch, ((customer*)b)->otch);
}

int city_cmp(const void* a, const void* b) {
	return strcmp(((customer*)a)->city, ((customer*)b)->city);
}

int street_cmp(const void* a, const void* b) {
	return strcmp(((customer*)a)->street, ((customer*)b)->street);
}

int house_cmp(const void* a, const void* b) {
	return ((customer*)a)->house_num - ((customer*)b)->house_num;
}

int flat_cmp(const void* a, const void* b) {
	return ((customer*)a)->flat_num - ((customer*)b)->flat_num;
}

int credit_cmp(const void* a, const void* b) {
	return ((customer*)a)->credit_card - ((customer*)b)->credit_card;
}

int code_cmp(const void* a, const void* b) {
	return ((customer*)a)->code_shop - ((customer*)b)->code_shop;
}
// Конец функций - указателей

// Функция сортировки по выбранному параметру, сортирует строки по алфавиту и числовые данные по возрастанию. Работает - проверено выводом в косноль и файл
void sorting(customer* customr, int count) {

	puts("Введите значение параметра для сортировки: ");
	//unsigned int param = menu_param(); // Выбор параметра

	// В зависимости от параметра, идет сортировка
	switch (menu_param()) {
	case 1: qsort(customr, count, sizeof(customer), famil_cmp);
		break;
	case 2: qsort(customr, count, sizeof(customer), name_cmp);
		break;
	case 3: qsort(customr, count, sizeof(customer), otch_cmp);
		break;
	case 4: qsort(customr, count, sizeof(customer), city_cmp);
		break;
	case 5: qsort(customr, count, sizeof(customer), street_cmp);
		break;
	case 6: qsort(customr, count, sizeof(customer), house_cmp);
		break;
	case 7: qsort(customr, count, sizeof(customer), flat_cmp);
		break;
	case 8: qsort(customr, count, sizeof(customer), credit_cmp);
		break;
	case 9: qsort(customr, count, sizeof(customer), code_cmp);
		break;
	default: break;
	}

	// Вывод отсортированного массива, файл исходных данных не трогается для сравнения результата
	puts("Отсортировано");
	print(customr, count);
	puts("Обновление файла вывода");
	output_file(customr, count);
}

// Функция очищения файлов
void clear_files() {
	FILE* data = fopen("..\\data.txt", "w");
	FILE* output = fopen("..\\output.txt", "w");
	fclose(data);
	fclose(output);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	customer* list_customers = (customer*)malloc(sizeof(customer) * MAX_LIST_CUSTOMERS_SIZE); // Массив структур с динамическим выделением памяти, макс. кол-во записей - MAX_LIST_CUSTOMERS_SIZE
	customer* customer = { 0 }; // Отдельный элемент массива структур
	unsigned count = read_data(list_customers); // Подсчет записей в массиве структур

	printf("На данный момент записей о покупателях: %u", count); // Сколько записей в исходных данных

	// Меню функций
	switch (menu_func()) {
	case 1: count = record_struct(list_customers, count); // Запись нового пользователя
		break;
	case 2:search(list_customers, count); // Поиск записи по параметру
		break;
	case 3:sorting(list_customers, count); // Сортировка массива структур
		break;
	case 4:print(list_customers, count); // Вывод структуры в консоль
		break;
	case 5:output_file(list_customers, count); // Вывод структуры в файл
		break;
	case 6: clear_files(); // Вызов очистки файлов
		break;
	case 7: // Если выбран выход из программы, очищаем память массива структур и прекращаем чтение кода
		free(list_customers);
		return 0;
	default: menu_func(); // Если введен номер, которого нет в списке, выводим список снова
	}

	main(); // Рекурсия главной функции для нового вызова меню и реализации других возможностей программы
}
