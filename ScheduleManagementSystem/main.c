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


struct schedule
{
    char title[30];
    char description[100];
    Times entry;
    Times expire;
};

typedef struct schedule Schedule;

struct node
{
    Schedule task;
    struct node *next;
};

typedef struct node List;


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
void scheduleMenus();

// List Functions Prototyping Starts Here


List* createNode(Schedule task);
void addToList(Schedule task);
void addToDone(Schedule task);
void removes(int index);
void displayList();
void displayDoneList();

// List Functions Prototyping Ends Here

// Schedule Operation Functions Starts Here

Schedule createSchedule();
void addSchedule();
void upNext();
void markDone();
void displayDone();
void displayNotDone();

// Schedule Operation Functions End Here


List *head;
List *done;

int currentYear;
int currentMonth;
int currentDay;
int listSize = 0;
int doneSize = 0;



int main()
{
    system("color 75");
    int choice, subMenus;

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

        case 2:
            do
            {
                system("CLS");
                scheduleMenus();
                scanf("%d", &subMenus);
                switch(subMenus)
                {
                case 0:
                    break;

                case 1:
                    addSchedule();
                    break;

                case 2:
                    upNext();
                    break;

                case 3:
                    markDone();
                    break;

                case 4:
                    displayNotDone();
                    break;

                case 5:
                    displayDone();
                    break;

                default:
                    printf("\n\n%40sInvalid Selections\n", " ");
                    break;
                }

                system("pause");

            }while(subMenus != 0);

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

    printf("1. Calendar%6s2. Schedule%6s3. Vacations%6s4. Help%6s0. Exit\n", " ", " ", " ", " ");
    printf("\n%50sEnter Choice : ", " ");


}

void scheduleMenus()
{
    printf("\n\n\n%40sSchedule Menus\n\n", " ");

    printf("%40s1. Create New Schedule\n", " ");
    printf("\n%40s2. Up Next Schedule\n", " ");
    printf("\n%40s3. Mark As Done\n", " ");
    printf("\n%40s4. View Active List\n", " ");
    printf("\n%40s5. View Done List\n", " ");
    printf("\n%40s0. Back To Menu\n", " ");

    printf("\n%40sEnter Choice : ", " ");
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

    sprintf(dates, "%d, %s %d; %d:%d", tm.wDay, getMonthNames(tm.wMonth), tm.wYear, tm.wHour, tm.wMinute);

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


// List Functions Start Here

List* createNode(Schedule task)
{
    List *newNode;
    newNode = (List*)malloc(sizeof(List));

    if(newNode == NULL)
    {
        return 0;
    }

    newNode->task = task;
    newNode->next = NULL;

    return newNode;

}

void addToList(Schedule task)
{
    char expOld[25], expNew[25];
    List *newNode = createNode(task);

    if(head == NULL)
    {
        head = newNode;
        head->next = NULL;
        listSize++;
        return;
    }

    strcpy(expOld, getCalendarString(head->task.expire));
    strcpy(expNew, getCalendarString(task.expire));

    List *temp = head;

    if(strcmp(expOld, expNew) == 1)
    {
        head = newNode;
        head->next = temp;
        listSize++;
        return;
    }

    while(temp->next != NULL)
    {
        strcpy(expOld, getCalendarString(temp->next->task.expire));

        if(strcmp(expOld, expNew) == 1)
        {
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    newNode->next = temp->next;
    temp->next = newNode;
    listSize++;
    return;
}


void addToDone(Schedule task)
{
    List *newNode = createNode(task);

    if(done == NULL)
    {
        done = newNode;
        done->next = NULL;
        doneSize++;
        return;
    }

    List *temp = done;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    doneSize++;
    return;
}

void removes(int index)
{
    if(index < 0 || index > listSize)
    {
        printf("Invalid Index\n");
        return;
    }

    if(index == 0)
    {
        head = head->next;
        listSize--;
        return;
    }

    List *temp = head;

    while(index - 1 > 0)
    {
        temp = temp->next;
        index--;
    }

    temp->next = temp->next->next;
    listSize--;

}

void displayList()
{
    List *temp = head;
    char start[25], end[25], title[30];
    int index = 0;

    printf("\n\n%20s%10s%30s%25s%25s\n", " ", "Index", "Title", "Created", "Expire");

    while(temp != NULL)
    {
        strcpy(start, getCalendarString(temp->task.entry));
        strcpy(end, getCalendarString(temp->task.expire));
        strcpy(title, temp->task.title);

        printf("%20s%10d%30s%25s%25s\n", " ", index++, title, start, end);
        temp = temp->next;

    }
    printf("\n");

}

void displayDoneList()
{
    List *temp = done;
    char start[25], end[25], title[30];
    int index = 0;

    printf("\n\n%20s%10s%30s%25s%25s\n", " ", "Index", "Title", "Created", "Expire");

    while(temp != NULL)
    {
        strcpy(start, getCalendarString(temp->task.entry));
        strcpy(end, getCalendarString(temp->task.expire));
        strcpy(title, temp->task.title);

        printf("%20s%10d%30s%25s%25s\n", " ", index++, title, start, end);
        temp = temp->next;

    }
    printf("\n");

}


Schedule createSchedule()
{
    char title[30], description[100];
    Times entry, expire;
    int dd, mm, yy, hr, min;

    Schedule temp;

    system("CLS");
    getchar();
    printf("\n\n%40sCreating New Schedule\n", " ");

    printf("\n%40s%10s : ", " ", "Title");
    gets(title);
    printf("\n%40s%10s : ", " ", "Description");
    gets(description);
    printf("\n%35s%15s : ", " ", "Expire Date");
    printf("\n%35s%15s : ", " ", "(dd mm yy hh mm)");
    scanf("%d %d %d %d %d", &dd, &mm, &yy, &hr, &min);

    expire.wDay = dd;
    expire.wMonth = mm;
    expire.wYear = yy;
    expire.wHour = hr;
    expire.wMinute = mm;

    entry = getCurrentTime();
    strcpy(temp.title, title);
    strcpy(temp.description, description);
    temp.entry = entry;
    temp.expire = expire;

    return temp;

}

void addSchedule()
{
    Schedule temp = createSchedule();

    addToList(temp);

    printf("\n\n\n%35sSchedule Successfully Added\n\n\n", " ");
}

void upNext()
{
    char entry[25], title[30], description[100], expire[25];

    system("CLS");
    if(head == NULL)
    {
        printf("\n\n\n%40sThere Is No Active Task\n\n", " ");
        return;
    }



    strcpy(entry, getCalendarString(head->task.entry));
    strcpy(expire, getCalendarString(head->task.expire));
    strcpy(title, head->task.title);
    strcpy(description, head->task.description);

    printf("\n\n%40sYour Next Task\n\n", " ");
    printf("%35s%15s %s\n", " ", "Title : ", title);
    printf("%35s%15s %s\n", " ", "Created On : ", entry);
    printf("%35s%15s %s\n", " ", "Expire On : ", expire);
    printf("%35s%15s %s\n", " ", "Description : ", description);

    printf("\n\n");

}

void markDone()
{
    Schedule tempSchedule;
    List *temp = head;

    int index;

    system("CLS");
    printf("\n\n%40sYour Schedule List", " ");
    printf("\n%40sEnter Index to Mark Done", " ");
    printf("\n\n%40sEnter -1 for Cancel Editing\n", " ");

    displayList();

    printf("\n\n%40sEnter Index : ");
    scanf("%d", &index);

    if(index == -1)
    {
        printf("\n%40sCancel Editing\n");
        return;
    }

    if(index < 0 || index > listSize)
    {
        printf("\n%40sInvalid Index\n", " ");
        return;
    }

    while(index - 1 > 0)
    {
        temp = temp->next;
        index--;
    }

    strcpy(tempSchedule.title, temp->task.title);
    strcpy(tempSchedule.description, temp->task.description);
    tempSchedule.entry = temp->task.entry;
    tempSchedule.expire = temp->task.expire;

    addToDone(tempSchedule);

    removes(index);

    printf("\n\n%30sSchedule Successfully Marked As Done\n", " ");

}


void displayDone()
{
    system("CLS");
    printf("\n\n%40sYou Have Done This Tasks\n\n", " ");

    displayDoneList();
}


void displayNotDone()
{
    system("CLS");

    printf("\n\n%40sYou Have This Tasks In Queue\n\n", " ");
    displayList();
}






