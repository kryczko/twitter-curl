#include <iostream>
#include <string>
#include <stdlib.h>

#include "curl.h"
#include "info.h"
#include "query.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    string query;
    int year, month, day;
    
    if (argc < 4) {
        cout << "ERROR: Not enough command line arguments.\n\nExample:\n$ ./twitter-curl DB2 2015 1 1\n\nThis will retrieve tweets since January 1st, 2015 up to the current day for each day while searching for the keyword DB2.\n\nExiting...\n";
        return 0;
    } else {
        query = argv[1];
        year = stoi(argv[2]);
        month = stoi(argv[3]);
        day = stoi(argv[4]);
    }
    
    system("mkdir -p queries");
    // Credentials from Twitter
    Global_Info my_info("b35e1f53fef9d989e102dc24de1b4c7b", "PIOpd1CE0Z", "cdeservice.mybluemix.net:443/api/v1/messages/search?q=");
    
    Global_Info.init_time(year, month, day);
    
    Query q("DB2_query", "DB2");
    
    string curl_string = "www.google.com";
    if (!curl(q, my_info)) { cout << "#####\nERROR: Could not curl the query with title: " << q.title << ". Exiting...\n#####\n"; exit(-1);}
    return 0;
}