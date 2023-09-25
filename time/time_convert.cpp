#include <iostream>

int main () {

    auto print_tm = [](struct tm t) {
        std::cout << t.tm_year << "-" << t.tm_mon << "-" << t.tm_mday << "-" << t.tm_hour << "-" << t.tm_min << "-" << t.tm_sec << std::endl;
    };

    // %H%M%S -> time_t struct
    auto convert_fmt_to_time = [](std::string fmt) -> struct tm {
        struct tm tm = {};
        strptime(fmt.c_str(), "%H%M%S", &tm);
        return tm;
    };

    struct tm start_time_tm = convert_fmt_to_time("000000");
    struct tm end_time_tm = convert_fmt_to_time("235959");

    print_tm(start_time_tm);
    print_tm(end_time_tm);
    

    int start_hour = start_time_tm.tm_hour;
    int end_hour = (end_time_tm.tm_min || end_time_tm.tm_sec) ? 
        end_time_tm.tm_hour + 1 : end_time_tm.tm_hour;

    std::cout << "st_hour " << start_hour << ", end_hour " << end_hour << std::endl;

    return 0;
}