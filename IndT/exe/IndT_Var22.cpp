// Copyright (c) 2023, ������ �.�., ��� �����, ����1-2
// 
// ����������: �������������� � ����������������
// �������������� ������� �1. ������� 22.
// 
// ���������� ���������, ������� ��������� ����������� ��������� � ��������� ����� �� ��������� ������ � ������. 
// ����� ������������ � ��������� ����. ����� ������� � ������ �� ��������� ���� ������ �����������.
// �������� ��� ������ ��������� � �������� ������ �������, ������� � ������� ��������� ������ �������� ������ ���� �� ����� ��������� ���������� �����.
// 
// ������� ������: ����� �������, ���������� ����� ���������.
// �������� ������: ���� report.txt � ������� ���������� ��� ���������� ������ ������� �������� ��� ������� ��������� �� �� ����������.
// 
// ��������� ����������: 24.12.2023
// 

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable : 4996)
#define MAX_DATA_SIZE 50 // ���� ������ ��� ����� ������ � ���������
#define MAX_LIST_SIZE 50 // ���� ������ ��� ������������� ��������� ������ ��������
#define REPORT_FN "..\\report.txt"
#define PARAM_FN "..\\param.ini"
#define SERVICE_FN "..\\service.txt"

// �������� ������ � ������� ����������� �����
struct complete_provides {
	char phone_number[16]; // ����� ��������
	unsigned int code; // ��� ������
	int date_day, date_mon, date_year; // ����: ����, ���, ���. � ��������� ���������� ��� ������� � ���������� ��������� ����
	unsigned int time; // ����� ������ � �������
	float phone_balance; // ������ ������
};

// ������� ��������� ������� � ������� �����. �������� ��������� - ��������� ��� �������� � ������� file_complete_provides_read
int time_mir(complete_provides* provide) {

	// ����������� ����������� ����
	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);
	int now_day = now->tm_mday, now_mon = now->tm_mon + 1, now_year = now->tm_year + 1900;

	int result = 0; // ��� ���������� ��� ����������� ����������

	// �������� - ���� �� ������ ������ � ������� ������, � ������ �� ����������� ���� � �������� ������
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

// ������� ���������� ���������� �� ����� param.ini
void file_params_read(int search_balance, unsigned int search_time) {
	FILE* file_param = fopen(PARAM_FN, "r");

	// ���������� - ������: ������ �����, �������� ������ ������� ���������, �������� ������ ������� ���������
	char stroke[256], str_balance[256], str_time[256];

	int data = 1; // ������� ����� - ����������, ��� ����������� ���������� ��������

	if (file_param == NULL) perror("Opening param.ini file error");
	else {

		while (fgets(stroke, sizeof(stroke), file_param) != NULL) {

			// ���� ������ �� �������� ������������ ��� ����������, ���������� ����� - ����������
			if (stroke[0] != ';' && stroke[0] != '[' && stroke[0] == 's') {
				if (data == 1) strcpy(str_balance, stroke);
				if (data == 2) strcpy(str_time, stroke);
				data++;
			}

		}

	}

	// ���������� �� ����� - ���������� �������� � ����������� ����������
	sscanf(str_balance, "search_phone_balance   = %i ", &search_balance);
	sscanf(str_time, "search_provide_time    = %u ", &search_time);

	printf("Balance for search: %d Time for search(min): %u\n", search_balance, search_time);
	fclose(file_param);
}

// ������� ������ ������ �� ����� � ����������� �� ������� � ������ � ���������. �������� ��������� - ������� printf ������� ��� ����������� ��������� �� �������
int file_complete_provides_read(complete_provides* provide) {
	FILE* file = fopen(SERVICE_FN, "r");
	unsigned int id = 0; // ���-�� ��������� ������, � ���������� ������������ ��� ����� ������ �������

	if (file == NULL) perror("Opening file for reading error");
	else {
		// ���������� - ������
		char file_line[256], complete_provide_date[20]; 
		puts("Provides list:");
		while (fgets(file_line, sizeof(file_line), file) != NULL) {
			sscanf(file_line, "%[^,], %u, %[^,], %u, %f ", &provide[id].phone_number, &provide[id].code, complete_provide_date, &provide[id].time, &provide[id].phone_balance); // ������ ������ �� �����
			sscanf(complete_provide_date, "%u.%u.%u", &provide[id].date_day, &provide[id].date_mon, &provide[id].date_year); // ���������� ���������� ������ � ����� �� ����, ���, ���
			provide[id].time = provide[id].time / 60; // ����������� ������ � ������

			printf("%s %i %i.%i.%i %i %.2f\n", provide[id].phone_number, provide[id].code, provide[id].date_day, provide[id].date_mon, provide[id].date_year, provide[id].time, provide[id].phone_balance);
			id++;
		}

	}

	fclose(file);
	return id;
}

// ������� ������ �� �������� ����������. �������� ��������� - ������� �����, ���� ���� ����������, ���� ���� �� ����� - ��� ������. ���������� - ���� ���� ����������
void search(complete_provides* provide, unsigned int complete_provides_cnt, int search_balance, unsigned int search_time) {
	
	FILE* output = fopen(REPORT_FN, "a");
	if (output == NULL) perror("Opening file output.txt for writing error");

	complete_provides* search_provides_buff = (complete_provides*)malloc(sizeof(complete_provides) * complete_provides_cnt); // ����� ��� ��������� ��������
	int week_result_count = 0, result_cnt = 0, res = 0; // ���-�� ������� � ������� �����������

	// ���� ������ �������� ��� �������, ����������� ������ - �����, ������� ����������� ����������� (� ���������� - ����� �������-������)
	for (int i = 0, k = 0; i <= complete_provides_cnt; i++) {
		if (provide[i].phone_balance >= search_balance && provide[i].time >= search_time && time_mir(&provide[i]) == 1) {
			search_provides_buff[k] = provide[i];
			k++;
			result_cnt++;
		}
	}

	// ����� �� ������ ���������� ��� ������� ��������. ���� ������� 7 ���������� ������� �� ������ � ������ - ����� ������
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

	// ���� �� ���� ����� �� ������, ����� �� ���������� ������
	if (res == 0) { 
		puts("\nData not found"); 
		fputs("Data not found", output);
	}


	free(search_provides_buff);
	fclose(output);
}


int main() {
	FILE* output = fopen(REPORT_FN, "w"); // � ������� ������, ��� �������� ����� ������������ ����� ���������� �����, ��� ������� ����������� ������ � �������� ������� ���������
	fclose(output); // ��� ��������� �����, � ������ ��������� ���� ����������� � ������ ����������, ����� ������� ������� ������

	complete_provides* complete_provides_list = (complete_provides*)malloc(sizeof(complete_provides) * MAX_LIST_SIZE); // ������ �������� � ������� �� �������
	unsigned int complete_provides_cnt = 0; // ���-�� ���������� ������� � ������ ��������
	float search_balance = 150; // �������� ������� ��� ������ �� ������
	unsigned int search_time = 1; // �������� ��� ������, ����� ��� ������ � ���

	file_params_read(search_balance, search_time); // ���������� ���������� �� ����� param.ini �������� ��� ������
	complete_provides_cnt = file_complete_provides_read(complete_provides_list) - 1; // ���������� ������ �� ������� �� ����� info.txt � ������ ��������

	search(complete_provides_list, complete_provides_cnt, search_balance, search_time); // ����� ������� ������ �� ������� ������� � ���������� �����������

	free(complete_provides_list); // ������������ ������ ���������� ��������

	return 0;
}