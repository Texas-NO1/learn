#include <iostream>
#include <time.h>
struct Date {
    int year, mon, day;

    Date() {}

    Date(const uint64_t timestamp) { 
        time_t time = timestamp;
        tm *t = localtime(&time);
        year = 1900 + t->tm_year;
        mon = 1 + t->tm_mon;
        day = t->tm_mday;
    }
    uint64_t toSeconds() {
        tm *t = new tm();
        std::cout << "Date : " << year << " " << mon << " " << day << std::endl;
        std::cout << "Before : " << t->tm_year << " " << t->tm_mon << " " << t->tm_mday << std::endl;
        t->tm_year = year - 1900;
        t->tm_mon = mon - 1;
        t->tm_mday = day;
        std::cout << "After : " << t->tm_year << " " << t->tm_mon << " " << t->tm_mday << std::endl;
        time_t seconds = mktime(t);
        return seconds;
    }
};

int main () {
    Date d;
    d.year = 2025;
    d.mon = 8;
    d.day = 16;
    std::cout << d.toSeconds() << std::endl;

    Date new_d(d.toSeconds());


    std::cout << new_d.year << " " << new_d.mon << " " << new_d.day << std::endl;
    return 0;
}