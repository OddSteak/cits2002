#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int first_day_of_month(int mon, int year);
void print_cal_line(char *line_break, int row, int offset, int days);
void print_cal(int month, int yr);
void print_yearly(int year);
void print_header(int mon, int year, char *line_break, int row, bool need_yr);
int no_of_days(int month, int year);
int calculate_rows(int offset, int days);

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
    for (int i = 0; i < 43; i++)
        printf(" ");
    printf("\033[1m%d\033[0m", year);
    for (int i = 0; i < 43; i++)
        printf(" ");
    printf("\n\n");

    char *line_break = "\t";
    char *line_break_last = "\n";

    for (int mon = 1; mon < 13; mon += 3)
    {
        int offset = first_day_of_month(mon, year);
        int offset2 = first_day_of_month(mon + 1, year);
        int offset3 = first_day_of_month(mon + 2, year);

        int rows1 = calculate_rows(offset, no_of_days(mon, year));
        int rows2 = calculate_rows(offset2, no_of_days(mon+1, year));
        int rows3 = calculate_rows(offset3, no_of_days(mon+2, year));

        // print 6 rows only if one of them needs it
        int rows = rows1 > 5 || rows2 > 5 || rows3 > 5 ? 6 : 5;

        for (int i = 1; i < 3; i++)
        {
            print_header(mon, year, line_break, i, false);
            print_header(mon + 1, year, line_break, i, false);
            print_header(mon + 2, year, line_break, i, false);
            printf("\n");
        }

        for (int j = 0; j < rows; j++)
        {
            print_cal_line(line_break, j, offset, no_of_days(mon, year));
            print_cal_line(line_break, j, offset2, no_of_days(mon + 1, year));
            print_cal_line(line_break_last, j, offset3, no_of_days(mon + 2, year));
        }
        printf("\n");
    }
}

// TODO: color current date
void print_cal(int mon, int year)
{
    char *line_break = "\n";

    int offset = first_day_of_month(mon, year);
    int rows = offset > 4 ? 6 : 5;

    for (int i = 1; i < 3; i++)
        print_header(mon, year, line_break, i, true);

    for (int i = 0; i < rows; i++)
        print_cal_line(line_break, i, offset, no_of_days(mon, year));
}

// TODO: left-handed support
void print_cal_line(char *line_break, int row, int offset, int days)
{
    int rows = offset > 4 ? 6 : 5;
    if (row >= rows)
    {
        for (int i = 0; i < 26; i++)
            printf(" ");
        printf("%s", line_break);
        return;
    }

    char buf[28];
    strcpy(buf, "");

    // TODO: make this loop suck less
    for (int i = row * 8 + 1; i < row * 8 + 9; i++)
    {
        if (i <= offset)
            strcat(buf, "    ");

        else if (i % 8 == 0)
            strcat(buf, line_break);

        else
        {
            int num = i - offset - (i / 8);
            if (num > days)
            {
                while (i != 8 * row + 7)
                {
                    strcat(buf, "    ");
                    i++;
                }
                strcat(strcat(buf, "  "), line_break);
                break;
            }
            else
            {
                char num_str[14];

                if (i == (row * 8) + 7)
                {
                    snprintf(num_str, 14, "%2d", num);
                    strncat(buf, num_str, 2);
                }
                else
                {
                    snprintf(num_str, 14, "%2d  ", num);
                    strncat(buf, num_str, 4);
                }
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

    tmv.tm_mon = month - 1;
    tmv.tm_year = year - 1900;

    if (row == 1)
    {
        char buf[27];
        if (need_yr)
            strftime(buf, 27, "         %Y %b         ", &tmv);
        else
            strftime(buf, 26, "           %b           ", &tmv);
        printf("%s%s", buf, line_break);
    }
    else
        printf("Su  Mo  Tu  We  Th  Fr  Sa%s", line_break);
}

int no_of_days(int month, int year)
{
    if (month == 2)
        return year % 4 ? 28 : 29;

    if (month < 8)
        return month % 2 ? 31 : 30;

    return month % 2 ? 30 : 31;
}

int calculate_rows(int offset, int days)
{
    if (days == 31)
        return offset > 4 ? 6 : 5;
    return offset > 5 ? 6 : 5;
}
