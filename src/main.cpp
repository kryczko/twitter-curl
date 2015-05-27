#include <iostream>
#include <string>
#include <stdlib.h>
#include "yaml-cpp/yaml.h"

#include "curl.h"
#include "info.h"

using namespace std;

void get_config(Global_Info& my_info) {
    YAML::Node config = YAML::LoadFile("query_input.yaml");
    YAML::Node queries = config["queries"];
    for (int i = 0; i < queries.size(); i ++) {
        Item item;
        item.title = queries[i]["title"].as<std::string>();
        item.query = queries[i]["query"].as<std::string>();
        YAML::Node start = queries[i]["startdate"];
        YAML::Node end = queries[i]["enddate"];
        item.startdate.year = start["year"].as<int>();
        item.startdate.month = start["month"].as<int>();
        item.startdate.day = start["day"].as<int>();
        item.enddate.year = end["year"].as<int>();
        item.enddate.month = end["month"].as<int>();
        item.enddate.day = end["day"].as<int>();
        item.init_times();
        my_info.config.queries.push_back(item);
    }
    
    cout << "Read configuration file, will now start curling...\n";
}

void call_api(Global_Info& my_info) {    
    for (auto& q : my_info.config.queries) {
        //q.update_current_time(); 
        //while (q.t_current < q.t_end) {
            if (!curl(q, my_info)) { 
                cout << "#####\nERROR: Could not curl the query with title: " << q.title << ". Exiting...\n#####\n"; 
                exit(-1);
            }
            //q.update_current_time(); 
            //}
    }
}

int main(int argc, char * argv[]) {
    
    system("mkdir -p queries");
    // Credentials from Twitter
    Global_Info my_info("b35e1f53fef9d989e102dc24de1b4c7b", "PIOpd1CE0Z", "cdeservice.mybluemix.net:443/api/v1/messages/search?q=");
    
    get_config(my_info);
    
    call_api(my_info);
    
    return 0;
}