#ifndef _INFO_H_
#define _INFO_H_
 
const int s_in_day = 24 * 60 * 60;

class Date {
public:
  int year, month, day;  
};

class Item {
public:
    std::string title;
    std::string query;
    Date startdate, enddate, currentdate, nextdate;
    
    time_t t_current, t_end, day_ahead;
    std::tm current, end, next_day;
    
    void init_times() {
        current.tm_year = startdate.year - 1900;
        current.tm_mon = startdate.month - 1;
        current.tm_mday = startdate.day;
        end.tm_year = enddate.year - 1900;
        end.tm_mon = enddate.month - 1;
        end.tm_mday = enddate.day;
        t_current = std::mktime(&current);
        t_end = std::mktime(&end);
        currentdate = startdate;
    } 
    
    void update_current_time() {
        t_current += s_in_day;
        day_ahead = t_current + s_in_day;
        currentdate.year = current.tm_year + 1900;
        currentdate.month = current.tm_mon + 1;
        currentdate.day = current.tm_mday;
        nextdate.year = next_day.tm_year + 1900;
        nextdate.month = next_day.tm_mon + 1;
        nextdate.day = next_day.tm_mday; 
    }
    
    std::string currentheader() {
        char header[1024];
        int n = sprintf(header, "queries/%s_%d-%02d-%02d.head", title.c_str(), currentdate.year, currentdate.month, currentdate.day);
        return header;
    }
    
    std::string currentbody() {
        char body[1024];
        int n = sprintf(body, "queries/%s_%d-%02d-%02d.body", title.c_str(), currentdate.year, currentdate.month, currentdate.day);
        return body;
    }
    
    std::string currentquery() {
        char start[100], end[100];
        int n = sprintf(start, "%d-%02d-%02d", currentdate.year, currentdate.month, currentdate.day);
        n = sprintf(end, "%d-%02d-%02d", enddate.year, enddate.month, enddate.day);
        return query + "%20posted%3A" + start + "%2C" + end + "&size=500";
    }
    
};

class Config {
public:
    std::vector<Item> queries;

};

class Global_Info {
public:
    std::string username;
    std::string password;
    std::string hostname;
    std::string total;
    
    Config config;
    
    Global_Info(std::string u, std::string p, std::string h) {
        this->username = u;
        this->password = p;
        this->hostname = h;
        this->total = "https://" + u + ":" + p + "@" + h;
    }
};

#endif