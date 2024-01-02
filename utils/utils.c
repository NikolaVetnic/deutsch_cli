/* taken from https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way */

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

char *trim_white_space(char *str);
void print_err(char *str);
int display_width(const char *s);

char *trim_white_space(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if (str == NULL)
    {
        return NULL;
    }
    if (str[0] == '\0')
    {
        return str;
    }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while (isspace((unsigned char)*frontp))
    {
        ++frontp;
    }
    if (endp != frontp)
    {
        while (isspace((unsigned char)*(--endp)) && endp != frontp)
        {
        }
    }

    if (frontp != str && endp == frontp)
        *str = '\0';
    else if (str + len - 1 != endp)
        *(endp + 1) = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if (frontp != str)
    {
        while (*frontp)
        {
            *endp++ = *frontp++;
        }
        *endp = '\0';
    }

    return str;
}

void print_err(char *str)
{
    printf("\x1b[1m\x1b[44m| ERROR |\x1b[0m %s \n\n", str);
}

int display_width(const char *s) {
    setlocale(LC_ALL, "");
    wchar_t wstr[256];
    int len = mbstowcs(wstr, s, 256);  // Convert multibyte to wide char
    if (len < 0) return strlen(s);  // Fallback in case of conversion failure

    int width = 0;
    for (int i = 0; i < len; ++i) {
        width += wcwidth(wstr[i]);
    }
    return width;
}