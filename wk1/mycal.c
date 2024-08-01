#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int first_day_of_month(int mon, int year);
void print_cal(char *line_break, int row, int offset);
void print_header(int mon, int year, char *line_break, int row);

int main(int ac, char **av)
{
    int mon, year;

    if (ac == 2)
    {
        year = atoi(av[1]);

        for (mon = 1; mon < 13; mon+=3)
        {
            char *line_break = "\t\t";

            int offset = first_day_of_month(mon, year);
            int offset2 = first_day_of_month(mon+1, year);
            int offset3 = first_day_of_month(mon+2, year);

            int rows = 6;   // offset > 4 ? 6 : 5;

            for (int i = 1; i<3; i++)
            {
                print_header(mon, year, line_break, i);
                print_header(mon+1, year, line_break, i);
                print_header(mon+2, year, line_break, i);
                printf("\n");
            }

            for (int j = 0; j < rows; j++)
            {
                print_cal(line_break, j, offset);
                print_cal(line_break, j, offset2);
                print_cal(line_break, j, offset3);
                printf("\n");
            }

            printf("\n");
        }
        return 0;
    }

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

    char *line_break = "\n";

    int offset = first_day_of_month(mon, year);
    int rows = offset > 4 ? 6 : 5;

    for (int i = 1; i<3; i++)
        print_header(mon, year, line_break, i);

    for (int i = 0; i < rows; i++)
    {
        print_cal(line_break, i, offset);
    }
}

void print_cal(char *line_break, int row, int offset)
{
    char buf[1000];
    strcpy(buf, "");

    for (int i = row * 8 + 1; i < row * 8 + 9; i++)
    {
        if (i <= offset)
        {
            strcat(buf, "    ");
        }

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

void print_header(int month, int year, char *line_break, int row)
{
    struct tm tmv;

    memset(&tmv, 0, sizeof(tmv));

    tmv.tm_mon = month - 1;
    tmv.tm_year = year - 1900;

    if (row == 1)
    {
        char buf[27];
        strftime(buf, 27, "        %Y %b          ", &tmv);
        printf("%s%s", buf, line_break);
    }
    else
        printf("Su  Mo  Tu  We  Th  Fr  Sa%s", line_break);
}
