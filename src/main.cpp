#include <iostream>
#include <string>
#include <stdlib.h>

#include "info.h"
#include "config.h"
#include "call_api.h"

using namespace std;


int main(int argc, char * argv[]) {
    
    system("mkdir -p queries");
    // Credentials from Twitter
    Global_Info my_info("b35e1f53fef9d989e102dc24de1b4c7b", "PIOpd1CE0Z", "cdeservice.mybluemix.net:443/api/v1/messages/search?q=");
    
    get_config(my_info);
    
    call_api(my_info);
    
    return 0;
}