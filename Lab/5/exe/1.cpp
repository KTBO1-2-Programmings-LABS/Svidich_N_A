// Copyright (c) 2023, ������ �.�., ��� �����, ����1-2
// 
// ��� ������������ ������ �5. ������� � 2. ������ �� �����������.
// 
// ��������� ����������: 22.12.2023

#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable : 4996)
#define MAX_INFO_SIZE 20 // ���� ������ ������ ������ � ���������
#define MAX_LIST_CUSTOMERS_SIZE 20 // ���� ������ ������ �����������
// ||

// �������� ��������� �������� ������
struct customer {
	char famil[MAX_INFO_SIZE]; // �������
	char name[MAX_INFO_SIZE]; // ���
	char otch[MAX_INFO_SIZE]; // ��������
	char city[MAX_INFO_SIZE]; // �����
	char street[MAX_INFO_SIZE]; // �����
	unsigned int house_num; // ���
	unsigned int flat_num; // ��������
	unsigned int credit_card; // �������
	unsigned int code_shop; // ��� �������
};

// ����� ������� ���� �������
int menu_func() {
	int choise;
	puts("\n���� �������: ");
	puts("1. �������� ������ ������������ \n2. ����� ������������ \n3. ���������� ������� �� ��������� \n4. ����� ������ ������������� � �������\n5. ����� ������ ������������� � ���� \n6. ������� ������ \n7. ����� �� ���������");
	puts("������� ����� �������: ");
	scanf("%i", &choise);
	return choise;
}

// ������� ������ ����� ���������. �������� ���������, ��������� ����� ������ � ����
int record_struct(customer* customer, unsigned id) {
	FILE* input = fopen("..\\data.txt", "a");
	int new_count;

	puts("���-�� ����� �������� ��� ������: ");
	scanf("%i", &new_count);

	if (input == NULL) perror("������ �������� ����� data.txt ��� ������ � �������� ������ � �����������");
	else {
		for (int i = 0; i < new_count; i++) {
			puts("���� ������ ����������: ");
			
			puts("�������: ");
			scanf("%s", &customer[id + i].famil);
			puts("���: ");
			scanf("%s", &customer[id + i].name);
			puts("��������: ");
			scanf("%s", &customer[id + i].otch);
			puts("�����: ");
			scanf("%s", &customer[id + i].city);
			puts("�����: ");
			scanf("%s", &customer[id + i].street);
			puts("����� ����: ");
			scanf("%u", &customer[id + i].house_num);
			puts("��������: ");
			scanf("%u", &customer[id + i].flat_num);
			puts("��������� �����: ");
			scanf("%u", &customer[id + i].credit_card);
			puts("��� �������: ");
			scanf("%u", &customer[id + i].code_shop);

			// ������ ���������� � ���� �������� ������, ����� �� ������ ������ ��� ����� ������� ��������� (������������ ������ ���, ����� ���������� ��������� � ���� �������)
			fprintf(input, "%s %s %s %s %s %u %u %u %u \n",
				customer[id + i].famil, customer[id + i].name, customer[id + i].otch, customer[id + i].city, customer[id + i].street,
				customer[id + i].house_num, customer[id + i].flat_num, customer[id + i].credit_card, customer[id + i].code_shop);

			puts("���� ��������.\n");
		}
	}

	fclose(input);
	return id;
}

// ������ ��� ������������ ������. ��������, ��������� ������� ���-�� ��� ������� ��� ����� ������� ���������
int read_data(customer* customr) {
	FILE* output = fopen("..\\data.txt", "r");
	unsigned count = 0;
	if (output == NULL) perror("������ �������� ����� data.txt ��� ������ ���������� � ����������� � ���������");
	else {

		char stroke[256];
		int i = 0;

		while (fgets(stroke, sizeof(stroke), output) != NULL) {
			sscanf(stroke, "%s %s %s %s %s %u %u %u %u \n", &customr[i].famil, &customr[i].name, &customr[i].otch, &customr[i].city, &customr[i].street, &customr[i].house_num, &customr[i].flat_num, &customr[i].credit_card, &customr[i].code_shop);
			count++;
			i++;
		}

	}
	if (count == 0) puts("������ ������ � ����������� ���\n");

	fclose(output);
	return count;
}

// ������� ������ �������� � �������. ��������, ��������� �� �������� - ���� �����
void print(customer* customr, int count) {

	if (customr == NULL) printf("��� �����������");
	else {
		puts("\n ������ � �����������: \n");
		for (int i = 0; i < count; i++) {
			printf("%s \t %s \t %s \t %s \t %s \t %d \t %d \t %d \t %d \n", &customr[i].famil, &customr[i].name, &customr[i].otch, &customr[i].city, &customr[i].street, customr[i].house_num, customr[i].flat_num, customr[i].credit_card, customr[i].code_shop);
		}
	}

}

// ������� ������ �������� � ����. ��������, ��������� ����� ������ � ����
void output_file(customer* customer, unsigned count) {
	FILE* file = fopen("..\\output.txt", "w");

	if (file == NULL) perror("������ �������� �����");
	else {

		if (customer == NULL) fprintf(file, "��� �����������");
		else {
			for (int i = 0; i < count; i++) {
				fprintf(file, "%s\t%s\t%s\t%s\t%s\t%u\t%u\t%u\t%u \n", customer[i].famil, customer[i].name, customer[i].otch, customer[i].city, customer[i].street, customer[i].house_num, customer[i].flat_num, customer[i].credit_card, customer[i].code_shop);
			}

			puts("����� ��������.\n");
		}
	}

	fclose(file);
}

// ������� ������ ������ ���������� ���������
unsigned int menu_param() {
	unsigned int choise;
	puts("������ ����������: ");
	puts("1.������� \n2.��� \n3.�������� \n4.����� \n5.����� \n6.����� ���� \n7.����� �������� \n8.����� ��������� �������� \n9.��� �������");
	puts("������� ����� ������� ���������: ");
	do {
		scanf("%u", &choise);
		printf("�������: %u\n", choise);
	} while (choise < 1 || choise > 9);
	return choise;
}

// ������� ������ �� �������� ���������. ��������, ��������� �� �������� - ���� �����
void search(customer* customer, int count) {
	char s_goal[MAX_INFO_SIZE]; // ��� ���������� ��� ��������� �� �������
	unsigned int int_goal = 0, param, res; // ��� ��������

	puts("������� �������� ��� ������: ");
	param = menu_param();
	puts("������� �������� ��������� ��� ������: ");
	// �� ����� ��������� ����������, ���������� ����� ��� ������
	if (param >= 6) 
		scanf("%s", &int_goal);
	else scanf("%s", &s_goal);

	// ������ �� ������� ������
	for (int i = 0; i <= count; i++) {
		// ���� ���� �� ���������� � ���������, ����� ������������
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
			if (res == 1) printf("�������: %s\t%s\t%s\t%s\t%s\t%u\t%u\t%u\t%u \n", 
				customer[i].famil, customer[i].name, customer[i].otch, customer[i].city, customer[i].street, customer[i].house_num, customer[i].flat_num, customer[i].credit_card, customer[i].code_shop);
	}
	if (res == 0) puts("���������� �� �������");
}

// ������� ��� �������� � qsort, �������� �� ���������� ��� ����������� ������
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
// ����� ������� - ����������

// ������� ���������� �� ���������� ���������, ��������� ������ �� �������� � �������� ������ �� �����������. �������� - ��������� ������� � ������� � ����
void sorting(customer* customr, int count) {

	puts("������� �������� ��������� ��� ����������: ");
	//unsigned int param = menu_param(); // ����� ���������

	// � ����������� �� ���������, ���� ����������
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

	// ����� ���������������� �������, ���� �������� ������ �� ��������� ��� ��������� ����������
	puts("�������������");
	print(customr, count);
	puts("���������� ����� ������");
	output_file(customr, count);
}

// ������� �������� ������
void clear_files() {
	FILE* data = fopen("..\\data.txt", "w");
	FILE* output = fopen("..\\output.txt", "w");
	fclose(data);
	fclose(output);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	customer* list_customers = (customer*)malloc(sizeof(customer) * MAX_LIST_CUSTOMERS_SIZE); // ������ �������� � ������������ ���������� ������, ����. ���-�� ������� - MAX_LIST_CUSTOMERS_SIZE
	customer* customer = { 0 }; // ��������� ������� ������� ��������
	unsigned count = read_data(list_customers); // ������� ������� � ������� ��������

	printf("�� ������ ������ ������� � �����������: %u", count); // ������� ������� � �������� ������

	// ���� �������
	switch (menu_func()) {
	case 1: count = record_struct(list_customers, count); // ������ ������ ������������
		break;
	case 2:search(list_customers, count); // ����� ������ �� ���������
		break;
	case 3:sorting(list_customers, count); // ���������� ������� ��������
		break;
	case 4:print(list_customers, count); // ����� ��������� � �������
		break;
	case 5:output_file(list_customers, count); // ����� ��������� � ����
		break;
	case 6: clear_files(); // ����� ������� ������
		break;
	case 7: // ���� ������ ����� �� ���������, ������� ������ ������� �������� � ���������� ������ ����
		free(list_customers);
		return 0;
	default: menu_func(); // ���� ������ �����, �������� ��� � ������, ������� ������ �����
	}

	main(); // �������� ������� ������� ��� ������ ������ ���� � ���������� ������ ������������ ���������
}
