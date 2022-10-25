#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <atlalloc.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
void out();
void input_patient(int total_lines,struct patient patients[30],struct sickness ill[30], struct doctor doc[30],struct hospital hosp[30],struct status stat[3]);
void del_patient(int line_num,struct patient patients[30], struct doctor doc[30], struct hospital hosp[30]);
void out_doc(int line, struct doctor doc[30]);
void out_hospital(int line, struct hospital hosp[30]);
void out_illness(int line, struct sickness ill[30], struct patient patients[30]);
void out_status(int line, struct status state[3], struct patient patients[30]);
void write_results(struct patient patients[30], struct sickness ill[30], struct doctor doc[30], struct hospital hosp[30]);

struct patient {
    int id=0;
    char name[25] = "";
    char diagnosis[40] = "";
    char state[20] = "";
}patients[30];

struct sickness {
    int id=0;
    char diagnosis[40] = "";
    char explanation[200] = "";
}ill[30];

struct doctor {
    int id=0;
    char patient_name[40] = "";
    char doctor_name[40] = "";
}doc[30];

struct hospital {
    int id=0;
    char doctor_name[40]="";
    char hospital_name[40]="";
}hosp[30];

struct status{
    int id=0;
    char patient_status[40] = "";
    char status_description[100] = "";
}state[3];

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char* locale = setlocale(LC_ALL, "RUS");
    int line_num,total_lines=1;
    patients[0] = { 1,"Алексей А.A.", "Грипп", "Здоров"};
    state[0] = {1,"Серьёзное","Необходимо постоянное наблюдение и уход за пациентом"};
    state[1] = { 1,"Умеренное","Не наблюдается тяжёлых ослажнений" };
    state[2] = { 1,"Здоров","Пациент здоров"};
    hosp[0] = {1,"Борисов Ф.А.", "Городская поликлиника №12"};
    doc[0] = {1,"Александр И.И.","Борисов Ф.А."};
    ill[0] = {1,"Грипп","Острое респираторное вирусное заболевание, вызываемое вирусами гриппа,поражающее верхние дыхательные пути"};
    int repeat = 1;
    do {
        out();
        printf("Введите:\n1-для просмотра данных о пациенте\n2-для просмотра данных о болезни\n3-для просмотра состояния пациета\n4-для удаления строки\n5-для добавления строки\n6-Записать таблицу в файл\n7-закрыть программу\n");
        int choice_patient,choice_doctor;
        do {
            scanf_s("%d", &choice_patient);
        } while (choice_patient > 7 || choice_patient < 1);
        switch (choice_patient)
        {
        case 1:
            printf("Введите номер пациента:\n");
            do {
                scanf_s("%d", &line_num);
            } while (line_num > total_lines || line_num < 1);
            out_doc(line_num, doc);
            printf("Введите:\n1-Просмотр информации о докторе\n2-Возвращение к предыдущей таблице\n");
            scanf_s("%d", &choice_doctor);
            switch (choice_doctor)
            {
            case 1:
                out_hospital(line_num,hosp);
                printf("Нажмите любую кнопку для возвращения в главную таблицу\n");
                _getch();
                break;
            default:
                break;
            }
            break;
        case 2:
            printf("Введите номер пациента:\n");
            do {
                scanf_s("%d", &line_num);
            } while (line_num > total_lines || line_num < 1);
            out_illness(line_num,ill,patients);
            printf("Нажмите любую кнопку для возвращения в главную таблицу\n");
            _getch();
            break;
        case 3:
            printf("Введите номер пациента:\n");
            do {
                scanf_s("%d", &line_num);
            } while (line_num > total_lines || line_num < 1);
            out_status(line_num,state,patients);
            printf("Нажмите любую кнопку для возвращения в главную таблицу\n");
            _getch();
            break;
        case 4:
            printf("Введите номер строки для удаления:\n");
            do {
                scanf_s("%d", &line_num);
            } while (line_num > total_lines || line_num < 1);
            del_patient(line_num, patients, doc, hosp);
            total_lines--;
            break;
        case 5:
            total_lines++;
            input_patient(total_lines, patients,ill,doc,hosp,state);
            break;
        case 6:
            write_results(patients, ill, doc, hosp);
            break;
        case 7:
            repeat = 0;
            break;
        default:
            break;
        }
    } while (repeat);
}
//Вывод таблицы пациентов//
void out() 
{
    int i = 0;
    printf("|id |ФИО пациета             |Диагноз пациента|Состояние пациента|\n");
    while (patients[i].id > 0)
    {
        printf("|%3d|%24s|%16s|%18s|\n", patients[i].id, patients[i].name, patients[i].diagnosis, patients[i].state);
        i++;
    }
    printf("------------------------------------------------------------------\n");
}
//Ввод новой строки//
void input_patient(int total_lines, struct patient patients[30], struct sickness ill[30], struct doctor doc[30], struct hospital hosp[30], struct status stat[3])
{
    patients[total_lines-1].id = total_lines;
    printf("Введите ФИО пациента:\n");
    do {
        gets_s(patients[total_lines - 1].name);
    } while (strlen(patients[total_lines - 1].name) == 0);
    printf("Введите ФИО лечащего доктора пациента:\n");
    do {
        gets_s(doc[total_lines - 1].doctor_name);
    } while (strlen(doc[total_lines - 1].doctor_name) == 0);
    strcpy(doc[total_lines - 1].patient_name, patients[total_lines - 1].name);
    printf("Введите название больницы доктора:\n");
    do {
        gets_s(hosp[total_lines - 1].hospital_name);
    } while (strlen(hosp[total_lines - 1].hospital_name) == 0);
    strcpy(hosp[total_lines - 1].doctor_name, doc[total_lines - 1].doctor_name);
    printf("Введите диагноз пациента:\n");
    int check = 0,ill_end=0;

    do {
        int i = 0;
        gets_s(patients[total_lines - 1].diagnosis);
        while (strlen(ill[i].diagnosis) > 0)
        {
            if (_stricmp(patients[total_lines - 1].diagnosis, ill[i].diagnosis) == 0)
                check = 1;
            i++;
        }
        if (check == 0)
        {
            printf("Был введен новый диагноз, введите его описание:\n");
            do {
                gets_s(ill[i].explanation);
            } while (strlen(ill[i].explanation) < 1);
            strcpy(ill[i].diagnosis, patients[total_lines - 1].diagnosis);
        }
    } while (strlen(patients[total_lines - 1].diagnosis)<1);

    //Ввод состояния пациента, пока оно не будет подходить уже существующим//
    
    printf("Введите состояние пациента (Здоров, Умеренное, Серьёзное):\n");
    do {
        gets_s(patients[total_lines - 1].state);
    } while (_stricmp(patients[total_lines - 1].state, stat[0].patient_status) != 0 && _stricmp(patients[total_lines - 1].state, stat[1].patient_status) != 0 && _stricmp(patients[total_lines - 1].state, stat[2].patient_status) != 0);

}
//Удаление строки//
void del_patient(int line_num, struct patient patients[30], struct doctor doc[30], struct hospital hosp[30])
{
    int i = 0,check=0;
    while (patients[i].id > 0 )
    {
        if (patients[i].id == line_num)
            check = 1;
        if (check)
        {
            patients[i].id = i+1;
            strcpy(patients[i].name, patients[i+1].name);
            strcpy(patients[i].diagnosis, patients[i+1].diagnosis);
            strcpy(patients[i].state, patients[i+1].state);
            strcpy(doc[i].patient_name, doc[i+1].patient_name);
            strcpy(doc[i].doctor_name, doc[i+1].doctor_name);
            strcpy(hosp[i].doctor_name, hosp[i+1].doctor_name);
            strcpy(hosp[i].hospital_name, hosp[i+1].hospital_name);
        }
        i++;
    }
    patients[i - 1].id = 0;

}
//Вывод данных о докторе//
void out_doc(int line, struct doctor doc[30]) 
{
    printf("|Пациент                  |Доктор                  |\n");
    printf("|%24s |%24s|\n",doc[line-1].patient_name,doc[line - 1].doctor_name);
    printf("----------------------------------------------------\n");
}
//Вывод данных о больнице//
void out_hospital(int line, struct hospital hosp[30])
{
    printf("|Доктор                  |Больница                 |\n");
    printf("|%24s|%24s|\n", hosp[line - 1].doctor_name, hosp[line - 1].hospital_name);
    printf("----------------------------------------------------\n");
}
//Вывод данных о болезни//
void out_illness(int line, struct sickness ill[30], struct patient patients[30])
{
    for (int i = 0; i < 3; i++)
        if (_stricmp(ill[i].diagnosis, patients[line - 1].diagnosis) == 0)
            printf("%s - %s\n", ill[i].diagnosis, ill[i].explanation);
}
//Вывод данных о состоянии пациента//
void out_status(int line, struct status state[3], struct patient patients[30])
{
    for (int i = 0; i < 3; i++)
        if (_stricmp(state[i].patient_status, patients[line - 1].state) == 0)
            printf("%s - %s\n", state[i].patient_status, state[i].status_description);
}
//Вывод результатов в файл//
void write_results(struct patient patients[30], struct sickness ill[30], struct doctor doc[30], struct hospital hosp[30])
{
    FILE* dev, * ved;
    dev = fopen("patients.txt", "w+");
    ved = fopen("staff.txt", "w+");
    int i = 0;
    fprintf(dev, "|id |ФИО пациета             |Диагноз пациента|Состояние пациента|\n");
    while (patients[i].id > 0)
    {
        fprintf(dev, "|%3d|%24s|%16s|%18s|\n", patients[i].id, patients[i].name, patients[i].diagnosis, patients[i].state);
        i++;
    }
    fprintf(dev, "------------------------------------------------------------------\n");
    fclose(dev);
    i = 0;
    fprintf(ved, "|Пациент                  |Доктор                  |Больница                 |\n");
    while (patients[i].id > 0)
    {
        fprintf(ved, "|%24s |%24s|%24s |\n", doc[i].patient_name, doc[i].doctor_name,hosp[i].hospital_name);
        i++;
    }
    fprintf(ved,"------------------------------------------------------------------------------\n");
    fclose(ved);
}