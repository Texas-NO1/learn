#include <iomanip>
#include <iostream>

int main () {
    struct tm tp;
    strptime("2023-10-09 10:59:23", "%Y-%m-%d %H:%M:%S", &tp);
    char buff[80];
    strftime(buff, sizeof(buff), "%Y%m%d%H%M%S", &tp);
    printf("%s\n", buff);
    tp.tm_mday += 1;
    tp.tm_hour += 1;
    tp.tm_min += 1;
    tp.tm_isdst = 0;
    time_t sec = mktime(&tp);
    strftime(buff, sizeof(buff), "%Y%m%d%H%M%S", &tp);
    printf("%s -> %ld (%d)\n", buff, sec, tp.tm_isdst);
}