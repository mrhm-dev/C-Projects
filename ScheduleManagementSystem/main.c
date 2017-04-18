#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#define VACATIONMAX 50

// these array contains the total days of months
int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// These string array contains month names
char monthNames[13][15] = {" ", "January", "February", "March",
                            "April", "May", "June", "July", "August",
                            "September", "October", "November", "December"};


//this is a structure to contain date and time
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


// this structure will contain only date for vacation list
struct date
{
    int day;
    int month;
    int year;
};

typedef struct date VacationDate;

// this structure will contain a single schedule
struct schedule
{
    char title[30];
    char description[100];
    Times entry;
    Times expire;
};

typedef struct schedule Schedule;

// this is node or structure of a list which contain Schedule type data
struct node
{
    Schedule task;
    struct node *next;
};

typedef struct node List;

// this structure will contain vacation details
struct vac
{
    char vacationName[100];
    int total;
    VacationDate startDate;
    VacationDate endDate;

};
typedef struct vac Vacation;


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
void help();

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

void writeDoneScheduleToFile();
void writeScheduleToFile();
void readDoneScheduleFromFile();
void readScheduleFromFile();

// Schedule Operation Functions End Here

// Vacation Functions Starts Here


void readVacations();
void searchVacationByMonth();
void displayNextVacation();
void displayAvailableVacations();
void displayAllVacations();
char* vacationVeiw(Vacation vac);

// Vacation Functions Ends Here

// this array will contain all vacations
Vacation vacationList[VACATIONMAX];
// vacationCount variable will count total vacations. Initially its zero
int vacationCount = 0;

// *head is the main list to contain all active schedule
List *head;

// *done is the list to contain completed list
List *done;


int currentYear;
int currentMonth;
int currentDay;
int listSize = 0;
int doneSize = 0;


// Main function starts here
int main()
{

    int choice, subMenus;

    // when main function starts it load all the data its need
    readScheduleFromFile();
    readDoneScheduleFromFile();

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
                    writeScheduleToFile();
                    writeDoneScheduleToFile();
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
            break;

        case 3:
            readVacations();
            do
            {
                system("CLS");
                vacationMenus();
                scanf("%d", &subMenus);

                switch(subMenus)
                {
                case 0:
                    break;

                case 1:
                    displayNextVacation();
                    break;

                case 2:
                    searchVacationByMonth();
                    break;

                case 3:
                    displayAvailableVacations();
                    break;

                case 4:
                    displayAllVacations();
                    break;

                default:
                    printf("\n\n%40sInvalid Input\n\n");
                    break;
                }

                system("pause");
            }while(subMenus != 0);
            break;

            case 4:
                help();
                break;

            default:
                printf("%40sInvalid Selection\n\n");
                break;
        }

    }while(choice != 0);

    return 0;
}
// main functions end here

// this function will display the menus
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

// this function will display schedule menus
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

// this function will display vacation Menu
void vacationMenus()
{
    printf("\n\n\n%40sVacation List Menus\n\n", " ");

    printf("%40s1. Upcoming Vacation\n", " ");
    printf("\n%40s2. Search Vacations By Month\n", " ");
    printf("\n%40s3. Available Vacations\n", " ");
    printf("\n%40s4. All Vacations\n", " ");
    printf("\n%40s0. Back To Menu\n", " ");

    printf("\n%40sEnter Choice : ", " ");
}

// All Calendar Functions Goes Here

// this function will capture the current time from the system
Times getCurrentTime()
{
    Times tm;
    GetSystemTime(&tm);

    tm.wHour = tm.wHour+6;

    if(tm.wHour > 24)
    {
        tm.wHour = tm.wHour - 24;
        tm.wDay = tm.wDay + 1;
    }

    return tm;
}

// this function will return a string of date given time
char* getCalendarString(Times tm)
{
    char dates[20];

    sprintf(dates, "%d, %s %d; %d:%d", tm.wDay, getMonthNames(tm.wMonth), tm.wYear, tm.wHour, tm.wMinute);

    return dates;
}

// this function will return month name according to month int value
char* getMonthNames(int month)
{
    return monthNames[month];
}

// tis function will return time string according to given time
char* getTimeString(Times tm)
{
    char times[20];

    sprintf(times, "%d : %d : %d", tm.wHour, tm.wMinute, tm.wSecond);

    return times;
}

// this function will check whether the year is leap year or not
bool isLeapYear(int year)
{
    if(year % 4 == 0 && year % 100 != 0) return true;
    if(year % 400 == 0) return true;

    return false;
}

// this function will calculate the day code according to calendar day
int dayCode(int day, int month, int year)
{
    int y = year - (14-month) / 12;
    int x = y + y/4 - y/100 + y/400;
    int m = month + 12 * ((14-month)/12) - 2;
    int d = day + x + (31*m) / 12 % 7;

    return d;
}

// this function will display calendar to the screen according to given date
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

// this function will construct current calendar day to the screen
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

// this function will reset the calendar instance to current date
void reset()
{
    Times tm = getCurrentTime();

    currentDay = tm.wDay;
    currentMonth = tm.wMonth;
    currentYear = tm.wYear;

    system("CLS");
    displayCalendar(currentDay, currentMonth, currentYear);
}

// this function will display next month's calendar
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

// this function will display previous month's calendar
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


// this function will jump to the calendar according the given month and year
void jump(int month, int year)
{
    system("CLS");
    displayCalendar(1, month, year);
}


// this function will display the full calendar of a given year
void displayFullCalendar(int year)
{
    int i;

    for(i=1; i<=12; i++)
    {
        displayCalendar(1, i, year);
        printf("\n\n");
    }
}

// this function will control the whole calendar system
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

// this function will take a Schedule type data and create a Node and return it
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

// this function will add a schedule type data to the list
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

// this function will add a schedule type data to the completed list after mark as done
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


// this function will remove schedule from active list
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

// this function will display the active list
void displayList()
{
    List *temp = head;
    char start[25], end[25], title[30];
    int index = 0;

    if(head == NULL)
    {
        printf("%40sThere are No Active Task\n\n", " ");
    }
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

// this function will display the done list
void displayDoneList()
{
    List *temp = done;
    char start[25], end[25], title[30];
    int index = 0;

    if(head == NULL)
    {
        printf("%40sThere are No Active Task\n\n", " ");
    }
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

// this function will get input from users , create a schedule and then return

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


// this function will add schedule to the list by calling addToList function
void addSchedule()
{
    Schedule temp = createSchedule();

    addToList(temp);

    printf("\n\n\n%35sSchedule Successfully Added\n\n\n", " ");
}

// this function will print the up next schedule
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

// this function will display all active list then mark as done according to index given by the user and then put it to the done list
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

// this function will display all done list
void displayDone()
{
    system("CLS");
    printf("\n\n%40sYou Have Done This Tasks\n\n", " ");

    displayDoneList();
}

// this function will display all active list
void displayNotDone()
{
    system("CLS");

    printf("\n\n%40sYou Have This Tasks In Queue\n\n", " ");
    displayList();
}


// this function will read all the vacations from the file
void readVacations()
{

    FILE *file;

    char name[100];
    int total, startD, endD, startM, endM;

    Vacation temp;
    VacationDate startDate, endDate;

    file = fopen("vacations.dat", "r");

    if(file == NULL)
    {
        exit(0);
    }

    while(true)
    {
        fgets(name, 255, (FILE *) file);

        if(strcmp(name, "ENDOFFILE") == 0)
        {
            break;
        }

        fscanf(file, "%d %d %d %d %d\n", &startD, &startM, &endD, &endM, &total);

        startDate.day = startD;
        startDate.month = startM;
        startDate.year = 2017;

        endDate.day = endD;
        endDate.month = endM;
        endDate.year = 2017;

        strcpy(temp.vacationName, name);
        temp.startDate = startDate;
        temp.endDate = endDate;
        temp.total = total;

        vacationList[vacationCount++] = temp;

    }
    fclose(file);

}

// this function will search for a vacation for the given month
void searchVacationByMonth()
{
    int mon, i;
    char vacView[250];

    system("CLS");
    printf("\n\n%40s Enter Month To Check Vacations\n\n", " ");
    printf("%40sEnter The Month Number (1 to 12) : ", " ");
    scanf("%d", &mon);

    printf("\n\n%40sThese Are The List\n\n", " ");
    for(i=0; i<vacationCount; i++)
    {
        if(vacationList[i].startDate.month == mon)
        {
            strcpy(vacView, vacationVeiw(vacationList[i]));
            printf("%35s%s\n\n", " ", vacView);
        }
    }

}

// this function will display the upcoming vacation
void displayNextVacation()
{
    int i;
    char vacView[250];

    Times tm = getCurrentTime();

    system("CLS");
    for(i=0; i<vacationCount; i++)
    {
        if(vacationList[i].startDate.month == tm.wMonth)
        {
            if(vacationList[i].startDate.day > tm.wDay)
            {
                strcpy(vacView, vacationVeiw(vacationList[i]));
                break;
            }
        }
        else if(vacationList[i].startDate.month > tm.wMonth)
        {
            strcpy(vacView, vacationVeiw(vacationList[i]));
            break;
        }
    }

    printf("\n\n\n%40sNext Upcoming Vacation : \n\n\n%35s%s\n\n\n\n", " ", " ", vacView);

}

// this function will display all available vacations in the year
void displayAvailableVacations()
{
    int i;
    char vacView[250];
    Times tm = getCurrentTime();

    system("CLS");
    printf("\n\n%40s These Are Available Vacation List\n\n", " ");
    for(i=0; i<vacationCount; i++)
    {
        if(vacationList[i].startDate.month > tm.wMonth)
        {
            strcpy(vacView, vacationVeiw(vacationList[i]));
            printf("%35s%s\n\n", " ", vacView);
        }
    }
}

// this function will display all vacations throw the year
void displayAllVacations()
{
    int i;
    char vacView[255];

    system("CLS");
    printf("\n\n%40s Full Vacation List of 2017\n\n", " ");
    for(i=0; i<vacationCount; i++)
    {
        strcpy(vacView, vacationVeiw(vacationList[i]));
        printf("%35s%s\n\n", " ", vacView);
    }
}

// this function will return a string of start date of a vacation
char* vacationVeiw(Vacation vac)
{
    char view[150], dat[100];

    strcpy(view, vac.vacationName);

    sprintf(dat , "%35sStart : %d/%d/%d To : %d/%d/%d; Total : %d", " ", vac.startDate.day, vac.startDate.month, vac.startDate.year,
            vac.endDate.day, vac.endDate.month, vac.endDate.year, vac.total);

    strcat(view, dat);

    return view;
}


// this function will read all schedule from the text file
void readScheduleFromFile()
{
    FILE *file;

    char title[30], description[100];
    int startD, startM, startY, startH, startMn;
    int endD, endM, endY, endH, endMn;
    int slen;

    Schedule temp;
    Times start, end;

    file = fopen("tasksdata.dat", "r");

    if(file == NULL)
    {
        exit(0);
    }

    while(!feof(file))
    {
        fgets(title, 30, (FILE *) file);
        slen = strlen(title);
        title[slen-1] = '\0';

        fgets(description, 100, (FILE *) file);
        slen = strlen(description);
        description[slen-1] = '\0';

        fscanf(file, "%d %d %d %d %d %d %d %d %d %d\n", &startD, &startM, &startY, &startH, &startMn, &endD, &endM, &endY, &endH, &endMn);

        start.wDay = startD;
        start.wMonth = startM;
        start.wYear = startY;
        start.wHour = startH;
        start.wMinute = startMn;

        end.wDay = endD;
        end.wMonth= endM;
        end.wYear = endY;
        end.wHour = endH;
        end.wMinute = endMn;

        strcpy(temp.title, title);
        strcpy(temp.description, description);

        temp.entry = start;
        temp.expire = end;

        addToList(temp);
    }


    fclose(file);
}


// this function will write data to the file
void writeScheduleToFile()
{
    FILE *file;
    List *temp = head;

    file = fopen("tasksdata.dat", "w+");

    if(file == NULL)
    {
        exit(0);
    }

    while(temp != NULL)
    {
        fprintf(file, "%s\n", temp->task.title);
        fprintf(file, "%s\n", temp->task.description);
        fprintf(file, "%d %d %d %d %d %d %d %d %d %d\n", temp->task.entry.wDay, temp->task.entry.wMonth, temp->task.entry.wYear, temp->task.entry.wHour, temp->task.entry.wMinute,
                temp->task.expire.wDay, temp->task.expire.wMonth, temp->task.expire.wYear, temp->task.expire.wHour, temp->task.expire.wMinute);

        temp = temp->next;
    }

    fclose(file);

}

// this function will read data from file
void readDoneScheduleFromFile()
{
    FILE *file;

    char title[30], description[100];
    int startD, startM, startY, startH, startMn;
    int endD, endM, endY, endH, endMn;
    int slen;

    Schedule temp;
    Times start, end;

    file = fopen("donetasksdata.dat", "r");

    if(file == NULL)
    {
        exit(0);
    }

    while(!feof(file))
    {
        fgets(title, 30, (FILE *) file);
        slen = strlen(title);
        title[slen-1] = '\0';

        fgets(description, 100, (FILE *) file);
        slen = strlen(description);
        description[slen-1] = '\0';

        fscanf(file, "%d %d %d %d %d %d %d %d %d %d\n", &startD, &startM, &startY, &startH, &startMn, &endD, &endM, &endY, &endH, &endMn);

        start.wDay = startD;
        start.wMonth = startM;
        start.wYear = startY;
        start.wHour = startH;
        start.wMinute = startMn;

        end.wDay = endD;
        end.wMonth= endM;
        end.wYear = endY;
        end.wHour = endH;
        end.wMinute = endMn;

        strcpy(temp.title, title);
        strcpy(temp.description, description);

        temp.entry = start;
        temp.expire = end;

        addToDone(temp);
    }


    fclose(file);
}

// this function will write data to the file
void writeDoneScheduleToFile()
{
    FILE *file;
    List *temp = done;

    file = fopen("donetasksdata.dat", "w+");

    if(file == NULL)
    {
        exit(0);
    }

    while(temp != NULL)
    {
        fprintf(file, "%s\n", temp->task.title);
        fprintf(file, "%s\n", temp->task.description);
        fprintf(file, "%d %d %d %d %d %d %d %d %d %d\n", temp->task.entry.wDay, temp->task.entry.wMonth, temp->task.entry.wYear, temp->task.entry.wHour, temp->task.entry.wMinute,
                temp->task.expire.wDay, temp->task.expire.wMonth, temp->task.expire.wYear, temp->task.expire.wHour, temp->task.expire.wMinute);

        temp = temp->next;
    }

    fclose(file);

}

void help()
{
    printf("%30sHello User, Here Goes some important command to control the calendar\n\n", " ");
    printf("%30snext ----- This command is for go to the next month\n", " ");
    printf("%30sprev ----- This command is for go to the previous month\n", " ");
    printf("%30sjump ----- This command is for go to Jump to the given month and year\n", " ");
    printf("%30sfull ----- This command is for go show the full calendar of a given year\n", " ");
    printf("%30sreset ----- This command will reset the display with current month\n", " ");
    printf("%30sback ----- This command will back to the main menu\n", " ");
}






