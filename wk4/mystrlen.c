#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int mystrlen(char *str);
bool isPalindrome(char *str);

int main()
{
    printf("%s palindrome\n", isPalindrome("lgrtrgl") ? "is" : "not");
    printf("%s palindrome\n", isPalindrome("lgrrgl") ? "is" : "not");
    printf("%s palindrome\n", isPalindrome("lgryrgl") ? "is" : "not");
    printf("%s palindrome\n", isPalindrome("lgeyrgl") ? "is" : "not");
    return 0;
}


int mystrlen(char *str)
{
    int count = 0;
    char c = str[0];

    while (c != 0)
        c = str[++count];

    return count;
}

bool isPalindrome(char *str)
{
    int len = mystrlen(str);

    int low = 0, high = len - 1;

    while (low < high) {
        if (str[low] != str[high])
            return false;
        low++; high--;
    }

    return true;
}
