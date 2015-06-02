#include <iostream>
#include <string>
#include <stdlib.h>

#include "info.h"
#include "config.h"
#include "call_api.h"

using namespace std;


int main(int argc, char * argv[]) {
    
    system("mkdir -p queries");
    system("mkdir -p queries/headers");
    system("mkdir -p queries/bodies");
    // Credentials from Twitter
    Global_Info my_info;
    my_info.hostname = "cdeservice.mybluemix.net:443/api/v1/messages/search?q=";
    get_config(my_info);
    my_info.set_url();
    call_api(my_info);    
    return 0;
}