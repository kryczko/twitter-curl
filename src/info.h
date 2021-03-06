#ifndef _INFO_H_
#define _INFO_H_

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <string>

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
    struct tm current, end, next_day;
    
    void init_times() {
        current = *localtime(&t_current);
        end = *localtime(&t_end);
        next_day = *localtime(&day_ahead);
        current.tm_year = startdate.year - 1900;
        current.tm_mon = startdate.month - 1;
        current.tm_mday = startdate.day;
        next_day.tm_year = startdate.year - 1900;
        next_day.tm_mon = startdate.month - 1;
        next_day.tm_mday = startdate.day + 1;
        end.tm_year = enddate.year - 1900;
        end.tm_mon = enddate.month - 1;
        end.tm_mday = enddate.day;
        t_current = mktime(&current);
        day_ahead = mktime(&next_day);
        t_end = mktime(&end);
        currentdate = startdate;
    } 
    
    void update_current_time() {
        current.tm_mday += 1;
        next_day.tm_mday += 1;
        t_current = mktime(&current);
        day_ahead = mktime(&next_day);
    }
    
    std::string current_date() {
        char date[1024];
        int n = sprintf(date, "%d-%02d-%02d", current.tm_year + 1900, current.tm_mon + 1, current.tm_mday);
        return date;
    }
    
    std::string currentheader() {
        char header[1024];
        int n = sprintf(header, "queries/headers/%s_%d-%02d-%02d.head", title.c_str(), current.tm_year + 1900, current.tm_mon + 1, current.tm_mday);
        return header;
    }
    
    std::string currentbody() {
        char body[1024];
        int n = sprintf(body, "queries/bodies/%s_%d-%02d-%02d.body", title.c_str(), current.tm_year + 1900, current.tm_mon + 1, current.tm_mday);
        return body;
    }
    
    std::string currentquery() {
        char start[100], end[100];
        int n = sprintf(start, "%d-%02d-%02d", current.tm_year + 1900, current.tm_mon + 1, current.tm_mday);
        n = sprintf(end, "%d-%02d-%02d", next_day.tm_year + 1900, next_day.tm_mon + 1, next_day.tm_mday);
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
    
    void set_url() {
        this->total = "https://" + this->username + ":" + this->password + "@" + this->hostname;
    }
};

#endif