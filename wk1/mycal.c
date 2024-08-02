#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int first_day_of_month(int mon, int year);
void print_cal_line(char *line_break, int row, int offset);
void print_cal(int month, int yr);
void print_yearly(int year);
void print_header(int mon, int year, char *line_break, int row, bool need_yr);

int main(int ac, char **av)
{
    if (ac == 2)
    {
        int year = atoi(av[1]);
        print_yearly(year);
        return 0;
    }

    int mon, year;

    if (ac == 3)
    {
        mon = atoi(av[1]);
        year = atoi(av[2]);
    }
    else
    {
        struct timeval cur_time;
        gettimeofday(&cur_time, NULL);
        struct tm *tmc;
        tmc = gmtime(&cur_time.tv_sec);
        mon = tmc->tm_mon + 1;
        year = tmc->tm_year + 1900;
    }

    print_cal(mon, year);
}

void print_yearly(int year)
{
    printf("\n");
    for (int i = 0; i<43; i++)
        printf(" ");
    printf("\033[1m%d\033[0m", year);
    for (int i = 0; i<43; i++)
        printf(" ");
    printf("\n\n");

    for (int mon = 1; mon < 13; mon += 3)
    {
        char *line_break = "\t";

        int offset = first_day_of_month(mon, year);
        int offset2 = first_day_of_month(mon + 1, year);
        int offset3 = first_day_of_month(mon + 2, year);

        int rows = 6;

        for (int i = 1; i < 3; i++)
        {
            print_header(mon, year, line_break, i, false);
            print_header(mon + 1, year, line_break, i, false);
            print_header(mon + 2, year, line_break, i, false);
            printf("\n");
        }

        for (int j = 0; j < rows; j++)
        {
            print_cal_line(line_break, j, offset);
            print_cal_line(line_break, j, offset2);
            print_cal_line(line_break, j, offset3);
            printf("\n");
        }

        printf("\n");
    }
}

// TODO: color today's date
void print_cal(int mon, int year)
{
    char *line_break = "\n";

    int offset = first_day_of_month(mon, year);
    int rows = offset > 4 ? 6 : 5;

    for (int i = 1; i < 3; i++)
        print_header(mon, year, line_break, i, true);

    for (int i = 0; i < rows; i++)
    {
        print_cal_line(line_break, i, offset);
    }
}

// TODO: left-handed support
void print_cal_line(char *line_break, int row, int offset)
{
    // TODO: calculate the correct buf size
    char buf[1000];
    strcpy(buf, "");

    // TODO: make this loop suck less
    for (int i = row * 8 + 1; i < row * 8 + 9; i++)
    {
        if (i <= offset)
            strcat(buf, "    ");

        else if (i % 8 == 0)
        {
            strcat(buf, line_break);
        }

        else
        {
            int num = i - offset - (i / 8);
            if (num > 31)
            {
                while (i != 8 * row + 7)
                {
                    strcat(buf, "    ");
                    i++;
                }
                strcat(buf, "  ");
                strcat(buf, line_break);
                break;
            }
            else
            {
                char num_str[14];

                if (i == (row * 8) + 7)
                    snprintf(num_str, 14, "%2d", num);
                else
                    snprintf(num_str, 14, "%2d  ", num);
                strcat(buf, num_str);
            }
        }
    }
    printf("%s", buf);
}

int first_day_of_month(int mon, int year)
{
    struct tm tmc;

    memset(&tmc, 0, sizeof(tmc));

    tmc.tm_mday = 1;
    tmc.tm_mon = mon - 1;
    tmc.tm_year = year - 1900;

    mktime(&tmc);

    return tmc.tm_wday;
}

void print_header(int month, int year, char *line_break, int row, bool need_yr)
{
    struct tm tmv;

    memset(&tmv, 0, sizeof(tmv));

    tmv.tm_mon = month - 1;
    tmv.tm_year = year - 1900;

    if (row == 1)
    {
        char buf[28];
        if (need_yr)
            strftime(buf, 27, "         %Y %b         ", &tmv);
        else
            strftime(buf, 27, "           %b           ", &tmv);
        printf("%s%s", buf, line_break);
    }
    else
        printf("Su  Mo  Tu  We  Th  Fr  Sa%s", line_break);
}

