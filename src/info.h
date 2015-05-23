#ifndef _INFO_H_
#define _INFO_H_

#include <ctime>

const int s_in_day = 24 * 60 * 60;

class Global_Info {
public:
    std::string username;
    std::string password;
    std::string hostname;
    std::string total;
    
    time_t start_date;
    time_t today = time(0);
    tm *start;
    tm *end;
    
    void init_time(int y, int m, int d) {
        start->tm_year = y - 1900;
        start->tm_mon = m - 1;
        start->tm_mday = d;
    }
    
    Global_Info(std::string u, std::string p, std::string h) {
        this->username = u;
        this->password = p;
        this->hostname = h;
        this->total = "https://" + u + ":" + p + "@" + h;
        time(&start_date);
        start = localtime(&start_date);
        end = localtime(&today);
    }
};

#endif