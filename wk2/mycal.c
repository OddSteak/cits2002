//  written by Chris.McDonald@uwa.edu.au
//
//  compile:  cc -std=c99 -Wall -Werror -o mycal mycal.c
//  run:      ./mycal [month [year]]


#include <stdio.h>              // required for printf()
#include <stdlib.h>             // required for atoi()

#include "first_day_of_month.c" // including C source usually strongly encouraged

//  THESE ARE OUR DEFAULT VALUES, USED IF COMMAND-LINE ARGS NOT PROVIDED
#define DEFAULT_MONTH           8
#define DEFAULT_YEAR            2023

#define NWEEKS                  6
#define DAYS_PER_WEEK           7

//  OUR print_cal() FUNCTION RECEIVES 2 ARGUMENTS, BUT DOESN'T RETURN A VALUE
void print_cal(int month, int year)
{
//  int day1        = 2;    // 1st Aug 2023 is a Tuesday

//  LATER, INITIALISE THIS WITH A CALL TO first_day_of_month(month, year);
    int day1        = first_day_of_month(month, year);

    int daysinmonth = 0;

    switch (month) {
        case 1: printf("   January %i\n", year);
                daysinmonth = 31;
                break;

        case 2: printf("   February %i\n", year);
                daysinmonth = 28;
                // check if it's a leap year??? => 29
                break;

//  ADD OTHER MONTHS
        case 8: printf("   August %i\n", year);
                daysinmonth = 31;
                break;
    }
    printf("Su Mo Tu We Th Fr Sa\n");

//  ITERATE OVER THE DIMENSIONS OF OUR 2-DIMENSIONAL GRID
    int day     = 1 - day1;

    for(int w=0 ; w<NWEEKS ; ++w) {
        for(int d=0 ; d<DAYS_PER_WEEK ; ++d) {
            if(day < 1 || day > daysinmonth) {
                printf(".. ");
            }
            else {
                printf("%2i ", day);   // format using 2 columns
            }
            ++day;
        }
        printf("\n");       // move printing to a new line after each week
    }

//  NOTHING TO RETURN TO main()
}

int main(int argcount, char *argvalue[ ])
{
//  INITIALISE LOCAL VARIABLES WITH DEFAULT VALUES
    int month   = DEFAULT_MONTH;
    int year    = DEFAULT_YEAR;

//  CHECK THE NUMBER OF COMMAND-LINE ARGUMENTS, POSSIBLY OVERRIDING DEFAULTS
//  ./mycal [month [year]]
    if(argcount > 1) {
        month   = atoi(argvalue[1]);    // convert argument (a string) to an int
        if(argcount > 2) {
            year    = atoi(argvalue[2]);
        }
    }

//  THE ACTUAL WORK IS PERFORMED BY ANOTHER FUNCTION, NOT IN main()
    print_cal(month, year);

    return 0;               // return 0 (= EXIT_SUCCESS) to operating system
}
