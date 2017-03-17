#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

char monthNames[13][15] = {" ", "January", "February", "March",
                            "April", "May", "June", "July", "August",
                            "September", "October", "November", "December"};

struct times
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMiliSecond;
};

typedef struct times Times;


// Prototyping Goes Here

// All Calendar Functions Prototyping Goes Here
Times getCurrentTime();
char* getCalendarString(Times tm);
char* getMonthNames(int month);
char* getTimeString(Times tm);
bool isLeapYear(int year);
int dayCode(int day, int month, int year);
void displayCalendar(int day, int month, int year);
void constructCalendar();
void next();
void prev();
void reset();
void jump(int month, int year);
void displayFullCalendar(int year);
void calendarControl();

// Calendar Functions Prototyping Ends Here

void menus();

int currentYear;
int currentMonth;
int currentDay;



int main()
{
    int choice;

    do
    {
        menus();
        scanf("%d", &choice);

        switch(choice)
        {
        case 0:
            break;

        case 1:
            calendarControl();
            break;

        }

    }while(choice != 0);

    return 0;
}

void menus()
{
    int i;

    system("CLS");
    constructCalendar();

    printf("\n\n%50sMenu List\n", " ");
    printf("%48s", " ");
    for(i=0; i<13; i++)
    {
        printf("-");
    }
    printf("\n\n%20s", " ");

    printf("1. Calendar%6s2. Schedule%6s3. Vacations%6s4. Help%6s0.Exit\n", " ", " ", " ", " ");
    printf("\n%50sEnter Choice : ", " ");


}

// All Calendar Functions Goes Here

Times getCurrentTime()
{
    Times tm;
    GetSystemTime(&tm);

    return tm;
}


char* getCalendarString(Times tm)
{
    char dates[20];

    sprintf(dates, "%d, %s %d", tm.wDay, getMonthNames(tm.wMonth), tm.wYear);

    return dates;
}

char* getMonthNames(int month)
{
    return monthNames[month];
}

char* getTimeString(Times tm)
{
    char times[20];

    sprintf(times, "%d : %d : %d", tm.wHour, tm.wMinute, tm.wSecond);

    return times;
}


bool isLeapYear(int year)
{
    if(year % 4 == 0 && year % 100 != 0) return true;
    if(year % 400 == 0) return true;

    return false;
}

int dayCode(int day, int month, int year)
{
    int y = year - (14-month) / 12;
    int x = y + y/4 - y/100 + y/400;
    int m = month + 12 * ((14-month)/12) - 2;
    int d = day + x + (31*m) / 12 % 7;

    return d;
}

void displayCalendar(int day, int month, int year)
{
    int i, dcode;

    if(isLeapYear(year))
    {
        monthDays[2] = 29;
    }

    dcode = dayCode(1, month, year);
    printf("\n\n%50s", " ");

    printf("%d, %s %d\n\n", day, getMonthNames(month), year);
    printf("%40s", " ");
    printf("%5s%5s%5s%5s%5s%5s%5s\n", "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa");

    printf("%40s", " ");
    for(i=0; i<38; i++)
    {
        printf("-");
    }

    printf("\n%40s", " ");
    for(i=0; i<dcode%7; i++)
    {
        printf("%5s", " ");
    }

    for(i=1; i<=monthDays[month]; i++)
    {
        printf("%5d", i);

        if((i+dcode)%7 == 0)
        {
            printf("\n%40s", " ");
        }
    }

    printf("\n%40s", " ");
    for(i=0; i<38; i++)
    {
        printf("-");
    }
    printf("\n");

}


void constructCalendar()
{
    Times tm = getCurrentTime();
    char timess[20];

    strcpy(timess, getTimeString(tm));

    currentDay = tm.wDay;
    currentMonth = tm.wMonth;
    currentYear = tm.wYear;

    system("CLS");
    displayCalendar(currentDay, currentMonth, currentYear);
    printf("%42sTimes : ( %s )\n", " ", timess);
}

void reset()
{
    Times tm = getCurrentTime();

    currentDay = tm.wDay;
    currentMonth = tm.wMonth;
    currentYear = tm.wYear;

    system("CLS");
    displayCalendar(currentDay, currentMonth, currentYear);
}


void next()
{
    currentMonth = currentMonth + 1;

    if(currentMonth > 12)
    {
        currentMonth = 1;
        currentYear = currentYear + 1;
    }

    system("CLS");
    displayCalendar(1, currentMonth, currentYear);
}


void prev()
{
    currentMonth = currentMonth - 1;

    if(currentMonth < 1)
    {
        currentMonth = 12;
        currentYear = currentYear - 1;
    }

    system("CLS");
    displayCalendar(1, currentMonth, currentYear);
}

void jump(int month, int year)
{
    system("CLS");
    displayCalendar(1, month, year);
}


void displayFullCalendar(int year)
{
    int i;

    for(i=1; i<=12; i++)
    {
        displayCalendar(1, i, year);
        printf("\n\n");
    }
}

void calendarControl()
{
    int month, year;
    char command[10];

    system("CLS");
    displayCalendar(currentDay, currentMonth, currentYear);

    do
    {


        printf("\n\n%40sEnter Your Commands (\"back\" for return)\n\n", " ");
        printf("%40sCommand >> ", " ");
        scanf("%s", command);

        if(strcmp(command, "next") == 0)
        {
            next();
        }
        else if(strcmp(command, "prev") == 0)
        {
            prev();
        }
        else if(strcmp(command, "jump") == 0)
        {
            scanf("%d %d", &month, &year);
            jump(month, year);
        }
        else if(strcmp(command, "full") == 0)
        {
            scanf("%d", &year);
            displayFullCalendar(year);
        }
        else if(strcmp(command, "reset") == 0)
        {
            reset();
        }
        else if(strcmp(command, "back") == 0)
        {
            break;
        }
        else
        {
            printf("%40sNot a Valid Command. See Help Section\n", " ");
        }
    }
    while(strcmp(command, "back") != 0);
}

// Calendar Functions Ends Here













