﻿#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <atlalloc.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

//Пациент//
class patient {
private:
    int id = 0;
    char name[25] = "";
    char diagnosis[40] = "";
    char state[20] = "";
public:
    patient(int new_id, const char new_patient_name[25], const char new_diagnosis[40], const char new_state[20])
    {
        id = new_id;
        strcpy(name, new_patient_name);
        strcpy(diagnosis, new_diagnosis);
        strcpy(state, new_state);
    }
public:
    patient(int new_id, char new_patient_name[25], char new_diagnosis[40], char new_state[20])
    {
        id = new_id;
        strcpy(name, new_patient_name);
        strcpy(diagnosis, new_diagnosis);
        strcpy(state, new_state);
    }
public:
    patient()
    {

    }
public:
    ~patient()
    {

    }

public:
    void out(patient patients[30])
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
    //void compare_status(int line, patient patients[30])
    //{
    //    if (_stricmp(patients[line].state, "Здоров") == 0)

    //}
public:
    void input_patient(int total_lines, patient patients[30],char patientname[40], char illnessname[40], char statusname[20])
    {
        patients[total_lines - 1].id = total_lines;
        strcpy(patients[total_lines - 1].name, patientname);
        strcpy(patients[total_lines - 1].diagnosis, illnessname);
        strcpy(patients[total_lines - 1].state, statusname);
    }

    //Вывод результатов в файл//
    void write_results(patient patients[30])
    {
        FILE* dev;
        dev = fopen("patients.txt", "w+");
        int i = 0;
        fprintf(dev, "|id |ФИО пациета             |Диагноз пациента|Состояние пациента|\n");
        while (patients[i].id > 0)
        {
            fprintf(dev, "|%3d|%24s|%16s|%18s|\n", patients[i].id, patients[i].name, patients[i].diagnosis, patients[i].state);
            i++;
        }
        fprintf(dev, "------------------------------------------------------------------\n");
        fclose(dev);
    }
    void patient_del(int line, patient patients[30])
    {
        int i = 0, check = 0;
        while (patients[i].id > 0)
        {
            if (patients[i].id == line)
                check = 1;
            if (check)
            {
                patients[i] = patients[i + 1];
                patients[i].id = i+1;
            }
            i++;
        }
        patients[i - 1].id = 0;
    }
};
//Болезнь//
class sickness {
private:
    int id=0;
    char diagnosis[40] = "";
    char explanation[200] = "";
public:
    sickness(int new_id, const char new_diagnosis[40], const char new_explanation[200])
    {
        id = new_id;
        strcpy(diagnosis, new_diagnosis);
        strcpy(explanation, new_explanation);
    }
public:
    sickness(int new_id,  char new_diagnosis[40], char new_explanation[200])
    {
        id = new_id;
        strcpy(diagnosis, new_diagnosis);
        strcpy(explanation, new_explanation);
    }
public:
    sickness()
    {

    }
public:
    ~sickness()
    {

    }
public:
    void ill_in(int total_lines,sickness ill[30],char illnessname[40])
    {
        int check = 0, ill_end = 0;
        ill[total_lines - 1].id = total_lines;
            int i = 0;
            while (strlen(ill[i].diagnosis) > 0)
            {
                if (_stricmp(illnessname, ill[i].diagnosis) == 0)
                    check = 1;
                i++;
            }
            strcpy(ill[total_lines - 1].diagnosis, illnessname);
            if (check == 0)
            {
                printf("Был введен новый диагноз, введите его описание:\n");
                do {
                    gets_s(ill[total_lines-1].explanation);
                } while (strlen(ill[total_lines - 1].explanation) < 1);
            }
    }
public:
    void out_illness(int line,  sickness ill[30])
    {
        for (int i = 0; i < 30; i++)
        {
            if (ill[i].id == line)
                printf("%s - %s\n", ill[i].diagnosis, ill[i].explanation);
        }
    }
};

class doctor {
private:
    int id=0;
    char patient_name[40] = "";
    char doctor_name[40] = "";
public:
    doctor()
    {

    }
public:
    doctor(int new_id, const char new_patient_name[40], const char new_doctor_name[40])
    {
        id = new_id;
        strcpy(patient_name, new_patient_name);
        strcpy(doctor_name, new_doctor_name);
    }
public:
    doctor(int new_id, char new_patient_name[40], char new_doctor_name[40])
    {
        id = new_id;
        strcpy(patient_name, new_patient_name);
        strcpy(doctor_name, new_doctor_name);
    }

public:
    void doc_del(int line,doctor doc[30])
    {
        int i = 0,check=0;
    while (doc[i].id > 0 )
    {
        if (doc[i].id == line)
            check = 1;
        if (check)
        {
            doc[i] = doc[i + 1];
            doc[i].id = i + 1;
        }
        i++;
    }
    doc[i-1].id = 0;
    }

    ~doctor()
    {

    }
    void write_doc(int i, doctor doc[30])
    {
        FILE* ved;
        ved = fopen("staff.txt", "a+");
        fprintf(ved, "|%24s ", doc[i].patient_name);
        fclose(ved);
    }
    void input_doc(int total_lines, doctor doc[30], char doctorname[40],char patientname[40])
    {
        doc[total_lines - 1].id = total_lines - 1;
        strcpy(doc[total_lines - 1].doctor_name, doctorname);
        strcpy(doc[total_lines - 1].patient_name, patientname);
    }
    ////Вывод данных о докторе//
void out_doc(int line,  doctor doc[30]) 
{
    printf("|Пациент                  |Доктор                  |\n");
    printf("|%24s |%24s|\n",doc[line-1].patient_name,doc[line - 1].doctor_name);
    printf("----------------------------------------------------\n");
}
};

class hospital{
private:
    int id=0;
    char doctor_name[40]="";
    char hospital_name[40]="";
public:
    hospital()
    {

    }
    void get_doctor_name(char new_doc_name[40])
    {
        strcpy(doctor_name, new_doc_name);
    }
public:
    hospital(int new_id, const char new_doctor_name[40], const char new_hospital_name[40])
    {
        id = new_id;
        strcpy(doctor_name, new_doctor_name);
        strcpy(hospital_name, new_hospital_name);
    }
    void input_hosp(int total_lines, hospital hosp[30], char doctorname[40], char hospitalname[40])
    {
        hosp[total_lines - 1].id = total_lines - 1;
        strcpy(hosp[total_lines - 1].doctor_name, doctorname);
        strcpy(hosp[total_lines - 1].hospital_name, hospitalname);
    }
public:
    void write_hosp(int i,hospital hosp[30])
    {
        FILE* ved;
        ved = fopen("staff.txt", "a+");
        fprintf(ved, "|%24s|%24s |\n", hosp[i].doctor_name,hosp[i].hospital_name);
        fclose(ved);
    }
    hospital(int new_id,  char new_doctor_name[40],  char new_hospital_name[40])
    {
        id = new_id;
        strcpy(doctor_name, new_doctor_name);
        strcpy(hospital_name, new_hospital_name);
    }
    ~hospital()
    {

    }
    void hosp_del(int line, hospital hosp[30])
    {
        int i = 0, check = 0;
        while (hosp[i].id > 0)
        {
            if (hosp[i].id == line)
                check = 1;
            if (check)
            {
                hosp[i] = hosp[i + 1];
                hosp[i].id = i + 1;
            }
            i++;
        }
        hosp[i - 1].id = 0;
    }
    //Вывод данных о больнице//
void out_hospital(int line,  hospital hosp[30])
{
    printf("|Доктор                  |Больница                 |\n");
    printf("|%24s|%24s|\n", hosp[line - 1].doctor_name, hosp[line - 1].hospital_name);
    printf("----------------------------------------------------\n");
}
};

class status{
private:
    int id;
    char patient_status[40] = "";
    char status_description[100] = "";
public:
    status(int new_id, const char new_status[40],const char new_description[100])
    {
        id = new_id;
        strcpy(patient_status, new_status);
        strcpy(status_description, new_description);
    }
    status()
    {

    }
    void out_state(int line, status state[30])
    {
        printf("%s - %s\n", state[line - 1].patient_status, state[line - 1].status_description);
    }
    void new_line(int total_lines, char statusname[20], status state[33])
    {
        int i;
        if (_stricmp(statusname, "Здоров") == 0)
            i = 0;
         if (_stricmp(statusname, "Умеренное") == 0)
             i = 1;
         if (_stricmp(statusname, "Серьёзное") == 0)
             i = 2;
         switch (i)
         {
         case 0:
             state[total_lines - 1] = state[30];
             state[total_lines - 1].id = total_lines - 1;
             break;
         case 1:
             state[total_lines - 1] = state[31];
             state[total_lines - 1].id = total_lines - 1;
             break;
         case 2:
             state[total_lines - 1] = state[32];
             state[total_lines - 1].id = total_lines - 1;
             break;
         default:
             break;
         }

    }
    void del_line(int line,status state[33])
    {
        int i = 0, check = 0;
        while (state[i].id > 0 && state[i].id<30)
        {
            if (state[i].id == line)
                check = 1;
            if (check)
            {
                state[i] = state[i + 1];
                state[i].id = i + 1;
            }
            i++;
        }
        state[i - 1].id = 0;
    }

    ~status()
    {

    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char* locale = setlocale(LC_ALL, "RUS");
    int line_num,total_lines=1;
    char patientname[40], doctorname[40], hospitalname[40], statusname[20],illnessname[40];
    patient* patients = new patient[30] { };
    patients[0] = { 1, "Алексей А.A.", "Грипп", "Здоров" };
    status *state = new status[33]{ };
    state[32]={32,"Серьёзное", "Необходимо постоянное наблюдение и уход за пациентом"};
    state[31] = {31,"Умеренное","Не наблюдается тяжёлых ослажнений" };
    state[30]= {30,"Здоров","Пациент здоров"};
    state[0] = { 1,"Здоров","Пациент здоров" };
    hospital  hosp[30];
    hosp[0] = {1,"Борисов Ф.А.", "Городская поликлиника №12"};
    doctor doc[30];
    doc[0] = {1,"Александр И.И.","Борисов Ф.А."};
    sickness* ill = new sickness[30] {};
    ill[0] = {1,"Грипп","Острое респираторное вирусное заболевание, вызываемое вирусами гриппа,поражающее верхние дыхательные пути"};
    int repeat = 1;
    do {
        patients->out(patients);
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
            doc->out_doc(line_num, doc);
            printf("Введите:\n1-Просмотр информации о докторе\n2-Возвращение к предыдущей таблице\n");
            scanf_s("%d", &choice_doctor);
            switch (choice_doctor)
            {
            case 1:
                hosp->out_hospital(line_num,hosp);
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
            ill->out_illness(line_num,ill);
            printf("Нажмите любую кнопку для возвращения в главную таблицу\n");
            _getch();
            break;
        case 3:
            printf("Введите номер пациента:\n");
            do {
                scanf_s("%d", &line_num);
            } while (line_num > total_lines || line_num < 1);
            state->out_state(line_num,state);
            printf("Нажмите любую кнопку для возвращения в главную таблицу\n");
            _getch();
            break;
        case 4:
            printf("Введите номер строки для удаления:\n");
            do {
                scanf_s("%d", &line_num);
            } while (line_num > total_lines || line_num < 1);
           patients->patient_del(line_num, patients);
           hosp->hosp_del(line_num, hosp);
           doc->doc_del(line_num, doc);
           state->del_line(line_num, state);
            total_lines--;
            break;
        case 5:
            total_lines++;
            printf("Введите ФИО пациента:\n");
                do {
                    gets_s(patientname);
                } while (strlen(patientname) == 0);
                printf("Введите ФИО лечащего доктора пациента:\n");
                do {
                    gets_s(doctorname);
                } while (strlen(doctorname) == 0);
                doc->input_doc(total_lines,doc,doctorname,patientname);
                printf("Введите название больницы доктора:\n");
                do {
                    gets_s(hospitalname);
                } while (strlen(hospitalname) == 0);
                hosp->input_hosp(total_lines, hosp, doctorname, hospitalname);
                printf("Введите диагноз пациента:\n");
                do {
                    gets_s(illnessname);
                } while (strlen(illnessname)==0);       
                ill->ill_in(total_lines, ill, illnessname);
                printf("Введите состояние пациента (Здоров, Умеренное, Серьёзное):\n");
                do {
                    gets_s(statusname);
                } while (_stricmp(statusname, "Здоров") != 0 && _stricmp(statusname, "Умеренное") != 0 && _stricmp(statusname, "Серьёзное") != 0);
                state->new_line(total_lines,statusname,state);
                patients->input_patient(total_lines, patients, patientname, illnessname, statusname);
            break;
        case 6:
           patients->write_results(patients);
           FILE* ved;
           ved = fopen("staff.txt", "w+");
           fprintf(ved, "|Пациент                  |Доктор                  |Больница                 |\n");
           fclose(ved);
           for (int i=0; i < total_lines; i++)
           {
               doc->write_doc(i, doc);
               hosp->write_hosp(i, hosp);
           }
           ved = fopen("staff.txt", "a+");
           fprintf(ved,"------------------------------------------------------------------------------\n");
           fclose(ved);

            break;
        case 7:
            repeat = 0;
            break;
        default:
            break;
        }
    } while (repeat);
    delete[] patients;
    delete[] ill;
    delete[] state; 
}
<<<<<<< Updated upstream
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
=======
>>>>>>> Stashed changes
