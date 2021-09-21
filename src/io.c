#include "jcbc/io.h"

#include <stdarg.h>

char* jcbc_fgets(char* s, int size, FILE* stream)
{
    char* r = fgets(s, size, stream);
    if (r) {
        int i = 0;
        while (i < size && s[i] != '\n') {
            ++i;
        }
        if (i < size) {
            s[i] = '\0';
        }
    }
    return r;
}

char* jcbc_popen(char* restrict out,
                 const int n,
                 const char* restrict cmd,
                 const int lines)
{
    FILE* temp = popen(cmd, "r");
    int l = 0;
    int i = 0;

    while (!feof(temp) && l+1 < n && (!lines || i < lines)) {
        fgets(out+l, n-l, temp);
        for (l = 0; out[l]; ++l);
        ++i;
    }

    if (l > 0) {
        out[l-1] = '\0';
    }

    pclose(temp);
    return out;
}

int jcbc_scanf(const char* restrict prompt,
               const char* restrict errMsg,
               void (* eofFunc)(),
               const char* const restrict fmt,
               ...)
{
    int n = 0;
    va_list vars;
    va_start(vars, fmt);

    {
        char prev = '\0';
        for (int i = 0; fmt[i]; ++i) {
            if (fmt[i] == '%' && prev != '\\') {
                ++n;
            }
            prev = fmt[i];
        }
    }

    fputs(prompt, stdout);

    int flag = vscanf(fmt, vars);

    while (flag != n && flag != EOF) {
        getchar();
        fputs(errMsg, stderr);
        flag = vscanf(fmt, vars);
    }

    va_end(vars);

    if (flag == EOF) {
        if (eofFunc) {
            eofFunc();
        }
        putchar('\n');
    }

    return flag;
}
