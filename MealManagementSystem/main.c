#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


#define DAY 32


/*
*       Here I declare a structure called member which will contain
*       Information of a member.
*       It has three properties.
*       name: name of the member; pay: how much he payed; meals[] to record his all meals
*/

struct member
{
        // This structure has three properties. Name, Pay and Meals[]
        char name[30];
        double pay[10];
        int meals[DAY];
};

// change type of struct member to Members
typedef struct member Members;

/*
* Here I declare the linked list structure
* which will contain data type Members
*/

struct lists
{
        // lists Contains Members type data
        Members info;
        struct lists *next;
};


// change type of struct lists to MemberList
typedef struct lists MemberList;


//This structure is for storing time and date values
struct times
{
        WORD wYear;
        WORD wMonth;
        WORD wDayOfWeek;
        WORD wDay;
        WORD wHour;
        WORD wMinute;
        WORD wSecond;
        WORD wMilliSecond;
};

// change type of struct times to Times
typedef struct times Times;

// this structure is for a single bazar day
struct dayB
{
    char bazars[30][30];
    int len;
};

// here we change the type of struct dayB to Bazar
typedef struct dayB Bazar;


//This Section is for prototyping
//Prototyping Starts Here

// display menu functions

void displayWelCome(void);
void displayMainMenu(void);
void displayMemberScreen(void);
void displayDailyTaskSection(void);
void displayReportSection(void);

// login registration section

void createMealTable(void);
int login(void);
int isMatchID(char id[]);

// Member List Section.. All Member List Functions
MemberList*  createNode(Members data);
void addMember(Members data);
void removeMember(int index);
void displayMembers(void);
Members get(int index);
int search(char *name);

// Member Section Functions
void initalZero(Members mem);
Members createMember(void);
void deleteMembers(void);
void searchMember(void);
void viewMemberInfo(int index);
void addBalance(void);
double sumOfPayments(Members mem);

// Times Functions
Times getTimes(void);
char* getTimeString(Times tm);
char* getWeekDay(int day);

// Report Section Functions
int membersTotalMeal(Members mem);
void viewDailyReport(void);
int totalMealDay(int day);
int totalMeal(void);
double accountBalance(void);
double totalCost(void);
double getBalance(void);
double mealRate(void);
double costForMeal(int meal);

// Daily Task Section Functions.
void updateDailyMeal(void);
void updateDailyCost(void);


//Prototyping Ends Here

//Instance Variable Section Starts Here

double costTable[DAY] = {0};
char nameOfMonth[20];
char idList[15][30];

MemberList *head;
int listSize = 0;
int paySize = 0;
int tableSize = 0;

// Instance Variable Section Ends Here

int main()
{
        int choice,  menu, submenu, mealDays, islogin;
        system("color 1f");

        do
        {
                system("CLS");
                displayWelCome();
                scanf("%d", &choice);

                switch(choice)
                {
                case 0:
                        printf("Exiting...!\n");
                        break;

                case 1:

                        islogin = login();

                        if(islogin == 1)
                        {
                                do
                                {
                                        system("CLS");
                                        displayMainMenu();
                                        scanf("%d", &menu);
                                        switch(menu)
                                        {
                                        case 0:
                                                break;

                                        case 1:
                                                do
                                                {
                                                        system("CLS");
                                                        displayMemberScreen();
                                                        scanf("%d", &submenu);
                                                        switch(submenu)
                                                        {
                                                        case 0:
                                                                break;

                                                        case 1:
                                                                addMemberToList();
                                                                break;

                                                        case 2:
                                                                deleteMembers();
                                                                break;

                                                        case 3:
                                                                searchMember();
                                                                break;

                                                        case 4:
                                                                system("CLS");
                                                                printf("\n\n%40s");
                                                                printf("Displaying All Members");
                                                                displayMembers();
                                                                break;

                                                        case 5:
                                                                addBalance();
                                                                break;

                                                        default:
                                                                printf("Not A Valid Entry\n");
                                                                break;
                                                        }
                                                        system("pause");
                                                }while(submenu != 0);

                                                break;

                                        case 2:
                                                do
                                                {
                                                        system("CLS");
                                                        displayDailyTaskSection();
                                                        scanf("%d", &submenu);

                                                        switch(submenu)
                                                        {
                                                        case 0:
                                                                break;

                                                        case 1:
                                                                updateDailyMeal();
                                                                break;

                                                        case 2:
                                                                updateDailyCost();
                                                                break;

                                                        default:
                                                                printf("Not A Valid Entry\n");
                                                                break;
                                                        }

                                                        system("pause");
                                                }while(submenu != 0);

                                                break;

                                        case 3:
                                                do
                                                {
                                                        system("CLS");
                                                        displayReportSection();
                                                        scanf("%d", &submenu);

                                                        switch(submenu)
                                                        {
                                                        case 0:
                                                                break;

                                                        case 1:
                                                                viewDailyReport();
                                                                break;

                                                        case 2:
                                                                break;
                                                                // this section will be complete soon.. Need File Function

                                                        default:
                                                                printf("Not A Valid Entry\n");
                                                                break;
                                                        }
                                                        system("pause");
                                                }while(submenu != 0);

                                                break;

                                        default:
                                                printf("Not A Valid Entry\n");
                                                break;
                                        }
                                        system("pause");
                                }while(menu != 0);
                        }
                        else
                        {
                                printf("Month And Password Not Match\n");
                                printf("Please Try Again With Proper Password\n");
                                printf("\n\nIf You Don't have Registered Yet, Please Create An Table First\n\n");
                        }
                        break;

                case 2:
                        createMealTable();
                        break;

                }

                system("pause");

        }
        while(choice != 0);

}



// ********************** This section declare all the function of MemberList**************************

// this createNode function create a node of Members
MemberList* createNode(Members data)
{
        MemberList* temp;
        temp = (MemberList *)malloc(sizeof(MemberList));

        if(temp == NULL)
        {
                printf("Memory Not Allocated\n");
                return 0;
        }

        temp->info = data;
        temp->next = NULL;

        listSize++;

        return temp;
}

// this addMember method add members to the MemberList with the help of createNode function
void addMember(Members data)
{
        MemberList *temp = createNode(data);

        if(head == NULL)
        {
                head = temp;
                head->next = NULL;
        }
        else
        {
                MemberList *current = head;

                while(current->next != NULL)
                {
                        current = current->next;
                }
                current->next = temp;
        }
}

// this removeMember method delete member from the MemberList and take index as a parameter
void removeMember(int index)
{
        if(index < 0 || index > listSize-1)
        {
                printf("Not A Valid Index\n");
                return;
        }

        if(index == 0)
        {
                head = head->next;
                listSize--;

                return;
        }
        else
        {
                MemberList *current = head;

                while(index-1>0)
                {
                        current = current->next;
                        index--;
                }

                current->next = current->next->next;
                listSize--;
        }
}

// this displayMembers function will display All Members in the MemberList
// It will display index number, name of member and how much they paid
void displayMembers()
{

        int i;

        printf("\n\n\n\n%50s", " ");
        printf("Member List\n");

        printf("%38s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }
        printf("\n\n");
        if(head == NULL)
        {
                printf("\n%40s", " ");
                printf("There Is No Member\n\n\n");
                return;
        }

        MemberList *current = head;
        int index = 0;

        printf("\n%40s", " ");
        printf("%10s%15s%10s\n", "Index", "Name", "Amount");
        while(current != NULL)
        {
                printf("\n%40s", " ");
                printf("%10d%15s%10.2lf\n", index++,  current->info.name, sumOfPayments(current->info));
                current =  current->next;
        }

        printf("\n");

}

// get members by using index number
Members get(int index)
{
        Members m;
         if(listSize == 0)
        {
                printf("There Are No Member Available\n");
                return m;
        }

        if(index <0 && index > listSize)
        {
                printf("Invalid Index\n");
                return m;
        }

        MemberList *current = head;
        while(current != NULL && index>0)
        {
                current = current->next;
                index--;
        }
        m = current->info;
        return m;
}

// search members using their name
int search(char *name)
{
        int ind = 0;
        MemberList *current = head;


        while(current != NULL)
        {
                if(strcmp(current->info.name, name) == 0)
                {
                        return ind;
                }
                else
                {
                        current = current->next;
                        ind++;
                }
        }
        return -1;
}

//********************End of MemberList function declaration*********************************




// this createMember function create a member By getting input
// Name and Pay. Then Initial meals to zero. then return this new Member
Members createMember(void)
{
        char name[30];
        double pay;
        Members  mem;
        int i;

        system("CLS");
        printf("\n\n\n\n\n%40s", " ");
        printf("Fill The Following Section Correctly\n");

        printf("%35s", " ");

        for(i=0; i<45; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n\n");

        printf("%40s%20s%5s", " ", "Enter The Name : ", " ");
        scanf("%s", &name);
        printf("\n\n%40s%20s%5s", " ", "Enter The Amount : ", " ");
        scanf("%lf", &pay);

        strcpy(mem.name, name);

        for(i=0; i<DAY; i++)
        {
                mem.meals[i] = -1;
        }

        for(i=0; i<10; i++)
        {
                mem.pay[i] = 0;
        }
        mem.pay[paySize++] = pay;

        printf("\n\n\n\n%40s", " ");
        printf("Member Creates Successfully.\n\n\n");

        return mem;

}

void addMemberToList(void)
{
        Members m = createMember();

        addMember(m);

}

// this method read an index from the user and delete member associated with that index
void deleteMembers()
{
        system("CLS");
        int ind, conf, i;

        printf("\n\n\n%40s", " ");
        printf("Select Index From Below To Delete\n");

        displayMembers();

        printf("\n\n%40s", " ");
        printf("Enter Index : ");
        scanf("%d", &ind);


        printf("\n\n\n%40s", " ");
        printf("Are Your Sure ? (1/0) : ");
        scanf("%d", &conf);

        if(conf == 1)
        {
                removeMember(ind);
                printf("\n\n%40s", " ");
                printf("Member Deleted Successfully\n");
        }
        else
        {
                printf("\n\n%40s", " ");
                printf("Cancel Deletion\n");
        }

        printf("\n\n");

}

// this method read name from user and show search result with the help of viewMemberInfo()
void searchMember()
{
        system("CLS");
        char name[30];
        int i;

        printf("\n\n\n\n%40s", " ");
        printf("Search Member Info\n");

        printf("%35s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n\n%40s", " ");
        printf("Enter Name To Search : ");
        scanf("%s", &name);

        int sear = search(name);

        if(sear != -1)
        {
                printf("\n\n%45s", " ");
                printf("Members Found !\n\n\n");
                viewMemberInfo(sear);
        }
        else
        {
                printf("\n\n%40s", " ");
                printf("Members Not Found!\n");
        }
}

// this method display members basic information when search found
void viewMemberInfo(int index)
{
        Members m = get(index);

        printf("\n\n");
        printf("%40s%10s : %-20s\n\n", " ", "Name", m.name);
        printf("%40s%10s : %-20.2lf\n\n", " ", "Paid", sumOfPayments(m));
        printf("%40s%10s : %-20d\n\n", " ", "Meal", membersTotalMeal(m));

        printf("\n");
}

void addBalance(void)
{
        system("CLS");
        char name[30];
        int ind = 0, conf, ch=1, i;
        double amt, previous;

        printf("\n\n\n\n%40s");
        printf("Add Balance To Members Account\n");

        printf("%35s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }
        printf("\n\n\n%40s", " ");
        printf("Enter The Name of The Member : ");
        scanf("%s", &name);

        MemberList *current = head;
        while(current != NULL)
        {
                if(strcmp(current->info.name, name) == 0)
                {
                        printf("\n\n%40s", " ");
                        printf("Member Found!\n");
                        viewMemberInfo(ind);
                        printf("\n\n%40s", " ");
                        printf("Enter Amount : ");
                        scanf("%lf", &amt);
                        printf("\n\n\n\n%40s", " ");
                        printf("Are You Sure?(1/0) : ");
                        scanf("%d",  &conf);

                        if(conf == 1)
                        {
                                current->info.pay[paySize++] = amt;

                                printf("\n\n%40s", " ");
                                printf("Amount Updated Successfully...\n");
                                ch = 0;
                                return;
                        }
                }
                else
                {
                        current = current->next;
                        ind++;
                }
        }

       if(ch)
       {
                printf("\n\n\n%40s", " ");
                printf("Members Not Found!\n");
       }

}

double sumOfPayments(Members m)
{
        int i;
        double sum = 0;

        for(i=0; i<paySize; i++)
        {
                sum = sum + m.pay[i];
        }

        return sum;
}

//********* Times Function Goes Here ************

// get Current time from the system and return it
Times getTimes()
{
       Times tm;
        GetSystemTime(&tm);

       return tm;
}

// get Date and day of week as a string
char* getTimeString(Times tm)
{
        char timeString[12];

       sprintf(timeString, "%d/%d/%d %s", tm.wDay, tm.wMonth, tm.wYear, getWeekDay(tm.wDayOfWeek));

        return timeString;
}

// determine the day of week and return its string representation
char* getWeekDay(int day)
{
        char weekDay[5];

        switch(day)
        {
        case 0:
                strcpy(weekDay, "SUN");
                break;

        case 1:
                strcpy(weekDay, "MON");
                break;

        case 2:
                strcpy(weekDay, "TUE");
                break;

        case 3:
                strcpy(weekDay, "WED");
                break;

        case 4:
                strcpy(weekDay, "THU");
                break;

        case 5:
                strcpy(weekDay, "FRI");
                break;

        case 6:
                strcpy(weekDay, "SAT");
        }

        return weekDay;
}


//************ Times Function Ends Here ******************


//************* Daily Task Section Starts here ***********************8

// this function will get input daily cost and store it
void updateDailyCost(void)
{
        Times tm = getTimes();
        char dat[30];
        double cost;
        int i;

        system("CLS");
        printf("\n\n\n\n%40s", " ");
        printf("Update Daily Cost");

        printf("\n%35s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n");

         if(costTable[tm.wDay] != 0)
        {
                printf("\n%40s", " ");
                printf("Already Updated\nYou Can't Change Any Data After Edited Once\n\n");
                return;
        }
        if(head == NULL)
        {
                printf("\n%40s", " ");
                printf("There is No Member Available. So You Can't Update Cost\n\n");
                return;
        }

        strcpy(dat, getTimeString(tm));

        printf("\n\n%40s", " ");
        printf("Today is : %s\n\n", dat);
        printf("%40s", " ");
        printf("Todays Cost is : ");
        scanf("%lf", &cost);


        costTable[tm.wDay] = cost;

        printf("\n\n\n\n%40sCost Successfully Updated\n\n\n", " ");
}


void updateDailyMeal(void)
{
        int m, i;
        MemberList *current = head;
        Times tm = getTimes();
        char ch[30];
        strcpy(ch, getTimeString(tm));

        system("CLS");
        printf("\n\n\n\n%40s", " ");
        printf("Update Daily Meal");

        printf("\n%35s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n\n%40s", " ");
        printf("Today is : %s\n", ch);


        if(head == NULL)
        {
                printf("\n\n%40s", " ");
                printf("There Are No Members Available\n");
                return;
        }



        if(current->info.meals[tm.wDay] != -1)
        {
                printf("\n\n%40s", " ");
                printf("Meal Already Updated\n%40sYou can't Edit Any Data After Editing it Once\n\n", " ");
                return;
        }

        printf("\n%40s", " ");
        printf("Enter Meals : \n");

        while(current != NULL)
        {
                printf("\n\n%40s", " ");
                printf("%10s%12s%10s%5s", "Name : ", current->info.name, "Meal : ", " ");
                scanf("%d", &m);
                current->info.meals[tm.wDay] =m;
                current = current->next;
        }
        printf("\n\n\n%40s", " ");
        printf("Meal Successfully Updated...\n");
}


// *************** Daily Task Section Ends Here ********************


// ***************** Report Section Starts Here **********************
//      this viewDailyReport display Report of the specific day
//      which day report will show it's depends on the calender



// this totalMeal Calculate Total meal of a specific day
int totalMealDay(int day)
{
        MemberList *current = head;
        int total = 0;

        while(current != NULL)
        {
                if(current->info.meals[day] != -1)
                {
                         total = total + current->info.meals[day];
                         current = current->next;
                }

        }

        return total;
}

// return total meals of a particular member
int membersTotalMeal(Members mem)
{
        int i, total = 0;

        for(i=0; i<DAY; i++)
        {
                if(mem.meals[i] != -1)
                {
                        total += mem.meals[i];
                }

        }

        return total;
}

// return total meals of the month
int totalMeal(void)
{
        MemberList *current = head;
        int total = 0;

        while(current != NULL)
        {
                total += membersTotalMeal(current->info);
                current = current->next;
        }
        return total;
}

double accountBalance(void)
{
        MemberList *current = head;
        double balance = 0;

        while(current != NULL)
        {
                balance += sumOfPayments(current->info);
                current = current->next;
        }

        return balance;
}

double totalCost(void)
{
        int i;
        double cost = 0;

        for(i=1; i<DAY; i++)
        {
                cost += costTable[i];
        }
        return cost;
}

double getBalance(void)
{
        return accountBalance() - totalCost();
}

double mealRate(void)
{
        return (totalCost()/totalMeal());
}

double costForMeal(int meal)
{
        return mealRate()*meal;
}

void viewDailyReport(void)
{
        int i, d1;
        double d2, d3, d4;
        Times tm = getTimes();
        char dt[15];
        strcpy(dt, getTimeString(tm));

        MemberList *current = head;

        system("CLS");
        printf("%35s%25s\n", " ", "Monthly Report : ");
        printf("%35s" , " ");
        for(i=0; i<40; i++)
        {
                printf("-");
        }
        printf("\n\n");

        printf("%27s%25s :  %-15s\n", " ", "Date", dt);
        printf("%27s%25s :  %-10.2lf\n", " ", "Account Balance", accountBalance());
        printf("%27s%25s :  %-10d\n", " ", "Total Meal", totalMeal());
        printf("%27s%25s :  %-10.2lf\n", " ", "Total Cost", totalCost());
        printf("%27s%25s :  %-10.2lf\n", " ", "Available Balance", getBalance());
        printf("%27s%25s :  %-10.2lf\n", " ", "Meal rate", mealRate());

        printf("\n%35s", " ");
        for(i=0; i<40; i++)
        {
                printf("=");
        }
        printf("\n\n\n");


        printf("%-25s%-15s%-15s%-15s%-15s%-15s\n", " ", "NAME", "TOTAL MEAL", "TOTAL PAID", "TOTAL COST", "TOTAL DUE");
        printf("%20s", " ");
        for(i=0; i<80; i++)
        {
                printf("-");
        }
        printf("\n");

        while(current != NULL)
        {
                d1 = membersTotalMeal(current->info);
                d2 = sumOfPayments(current->info);
                d3 = costForMeal(d1);
                d4 = d3-d2;
                printf("%-25s%-15s%-15d%-15.2lf%-15.2lf%-15.2lf\n",  " " , current->info.name, d1, d2, d3, d4);

                current = current->next;
        }

        printf("%20s", " ");
        for(i=0; i<80; i++)
        {
                printf("-");
        }
        printf("\n");



}


// ******************* Report Section Ends Here ***************************



// ********************** Menu Designing Section starts Here ************************

void displayWelCome(void)
{
        int i;
        printf("\n\n\n\n%30s", " ");
        for(i=0; i<50; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n%31s%40s\n\n", " ", "Welcome To Meal Management System");
        printf("%30s", " ");
        for(i=0; i<50; i++)
        {
            printf("%c", '-');
        }


        printf("\n\n\n\n");
        printf("%35s%10s%-30s\n\n", "[ 1 ]", " ", "Login To Meal Table");
        printf("%35s%10s%-30s\n\n", "[ 2 ]", " ", "Create New Meal Table");
        printf("%35s%10s%-30s\n\n", "[ 0 ]", " ", "Exit From The System");

        printf("%30s", " ");
        for(i=0; i<50; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n%35s%-30s", " ", "Enter Your Choice : ");


}

void displayMainMenu(void)
{
        int i;
        printf("\n\n\n\n%40s", " ");
        printf("Meal Management System\n");

        printf("%30s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n");

        printf("%40s%10s%-30s\n", "[ 1 ]", " ", "MEMBERS" );
        printf("%40s%10s%-30s\n", "[ 2 ]", " ", "DAILY TASK" );
        printf("%40s%10s%-30s\n", "[ 3 ]", " ", "CHECK REPORT" );
        printf("%40s%10s%-30s\n", "[ 0 ]", " ", "LOGOUT" );

        printf("\n\n%30s", " ");
        for(i=0; i<40; i++)
        {
                printf("%c", '-');
        }
        printf("\n\n\n");

        printf("%35s%-25s%2s", " ", "ENTER YOUR CHOICE : " , " ");

}

void displayMemberScreen(void)
{
        int i;
        printf("\n\n\n\n%40s", " ");
        printf("Member Section\n");

        printf("%30s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n");

        printf("%40s%10s%-30s\n", "[ 1 ]", " ", "Add New Member" );
        printf("%40s%10s%-30s\n", "[ 2 ]", " ", "Delete Member" );
        printf("%40s%10s%-30s\n", "[ 3 ]", " ", "Search Member" );
        printf("%40s%10s%-30s\n", "[ 4 ]", " ", "View All Member" );
        printf("%40s%10s%-30s\n", "[ 5 ]", " ", "Add Balance" );
        printf("%40s%10s%-30s\n", "[ 0 ]", " ", "Back To Main Menu" );

        printf("\n\n%30s", " ");
        for(i=0; i<40; i++)
        {
                printf("%c", '-');
        }
        printf("\n\n\n");

        printf("%35s%-25s%2s", " ", "ENTER YOUR CHOICE : " , " ");

}

void displayDailyTaskSection(void)
{
        int i;
        printf("\n\n\n\n%40s", " ");
        printf("Meal Management System\n");

        printf("%30s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n");

        printf("%40s%10s%-30s\n", "[ 1 ]", " ", "Update Meal" );
        printf("%40s%10s%-30s\n", "[ 2 ]", " ", "Update Cost" );
        printf("%40s%10s%-30s\n", "[ 0 ]", " ", "Back To Main Menu" );

        printf("\n\n%30s", " ");
        for(i=0; i<40; i++)
        {
                printf("%c", '-');
        }
        printf("\n\n\n");

        printf("%35s%-25s%2s", " ", "ENTER YOUR CHOICE : " , " ");

}


void displayReportSection(void)
{
        int i;
        printf("\n\n\n\n%40s", " ");
        printf("Meal Management System\n");

        printf("%30s", " ");
        for(i=0; i<40; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n");

        printf("%40s%10s%-30s\n", "[ 1 ]", " ", "View FUll Report" );
        printf("%40s%10s%-30s\n", "[ 2 ]", " ", "Make A FIle" );
        printf("%40s%10s%-30s\n", "[ 0 ]", " ", "Back To Main Menu" );

        printf("\n\n%30s", " ");
        for(i=0; i<40; i++)
        {
                printf("%c", '-');
        }
        printf("\n\n\n");

        printf("%35s%-25s%2s", " ", "ENTER YOUR CHOICE : " , " ");

}




// ******************* Menu designing Section ends here *****************************

// *********************create Account Section Starts Here***************************

void createMealTable(void)
{
        char monthName[15], pass[15];
        char id[30];
        int i;
        system("CLS");
        printf("\n\n\n\n");
        printf("%35s%-30s\n", " ", "FILL THE FORM BELOW");
        printf("%35s", " ");
        for(i=0; i<20; i++)
        {
            printf("%c", '-');
        }
        printf("\n\n\n\n");
        printf("%35s%-25s%3s", " ", "Enter Month Name: ", " ");
        scanf("%s", &monthName);

        printf("\n\n%35s%-25s%3s", " ", "Enter Your Password: ", " ");
        scanf("%s", &pass);

        strcpy(id, monthName);
        strcat(id, pass);

        strcpy(idList[tableSize], id);
        tableSize++;
        printf("\n\n\n\n%30s", " ");
        printf("Your Account Successfully Created...!\n\n");
        printf("%30s", " ");
        printf("You Can Now Login To System\n\n\n\n");
}


int login(void)
{
        int i;
        char name[15], pass[15], id[30];
        system("CLS");
        printf("\n\n\n\n%35s", " ");
        printf("Login To Meal Management System");

        printf("\n\n%35s", " ");
        printf("Enter Month Name And Password Correctly");

        printf("\n\n%30s", " ");
        for(i=0; i<50; i++)
        {
            printf("%c", '-');
        }

        printf("\n\n\n%35s", " ");

        printf("%-15s%3s", "Month Name : ", " ");
        scanf("%s", &name);

        printf("\n\n%35s", " ");
        printf("%-15s%3s", "Password : ", " ");
        scanf("%s", &pass);

        printf("\n\n\n");

        strcpy(id, name);
        strcat(id, pass);

        if(isMatchID(id) == 1)
        {
            printf("\n%30s%-30s\n\n", " ", "Access Granted");
            return 1;
        }

        return -1;
}

int isMatchID(char id[])
{
        int i;

        for(i=0; i<tableSize; i++)
        {
                if(strcmp(idList[i], id) == 0)
                {
                        return 1;
                }
        }
        return -1;
}

// *********************** Create Account Section Ends Here ****************************















