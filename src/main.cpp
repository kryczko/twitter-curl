#include <iostream>
#include "curl.h"
#include <string>

using namespace std;

bool curl(string url, string header, string body) {
    /* Since we are using a C library, we need to convert
       the strings to chars. In C++, it is much more conv
       enient to use string.                             */
    
    char char_url[1024], char_head[1024], char_body[1024];
    strncpy(char_url, url.c_str(), sizeof(char_url));
    strncpy(char_head, header.c_str(), sizeof(char_head));
    strncpy(char_body, body.c_str(), sizeof(char_body));
    if (!c_curl(char_url, char_head, char_body)) {
        cout << "*** Success with url: " << url << " ***\n";
        return true;
    } 
    return false;
}

class Global_Info {
public:
    string username;
    string password;
    string hostname;
    string total;
    Global_Info(string u, string p, string h) {
        this->username = u;
        this->password = p;
        this->hostname = h;
        this->total = "https://" + u + ":" + p + "@" + h;
    }
};

class Query {
public:
    string title;
    string query;
    string head;
    string body;
    Query(string t, string q) {
        this->title = t;
        this->query = q;
        this->head = t + "_head.out";
        this->body = t + "_body.out";
    }
};

int main(int argc, char * argv[]) {
    
    // Credentials from Twitter
    Global_Info my_info("b35e1f53fef9d989e102dc24de1b4c7b", "PIOpd1CE0Z", "cdeservice.mybluemix.net:443/api/v1/messages/search?q=");
    
    Query q("DB2_query", "DB2");
    
    string curl_string = "www.google.com";
    if (!curl(my_info.total + q.query, q.head, q.body)) { cout << "#####\nERROR: Could not curl the string: " << q.query << ". Exiting...\n#####\n"; exit(-1);}
    return 0;
}