#include <iostream>
#include <string>
#include <stdlib.h>

#include "curl.h"
#include "info.h"
#include "query.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    system("mkdir -p queries");
    // Credentials from Twitter
    Global_Info my_info("b35e1f53fef9d989e102dc24de1b4c7b", "PIOpd1CE0Z", "cdeservice.mybluemix.net:443/api/v1/messages/search?q=");
    
    Query q("DB2_query", "DB2");
    
    string curl_string = "www.google.com";
    if (!curl(q, my_info)) { cout << "#####\nERROR: Could not curl the string: " << q.query << ". Exiting...\n#####\n"; exit(-1);}
    return 0;
}