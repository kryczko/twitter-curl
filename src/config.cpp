#include "yaml-cpp/yaml.h"
#include "info.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>

void get_config(Global_Info& my_info) {
    YAML::Node config = YAML::LoadFile("query_input.yaml");
    YAML::Node queries = config["queries"];
    YAML::Node cred = config["twitter-api"];
    my_info.username = cred["username"].as<std::string>();
    my_info.password = cred["password"].as<std::string>();
    
    for (int i = 0; i < queries.size(); i ++) {
        Item item;
        item.title = queries[i]["title"].as<std::string>();
        item.query = queries[i]["query"].as<std::string>();
        YAML::Node start = queries[i]["startdate"];
        YAML::Node end = queries[i]["enddate"];
        item.startdate.year = start["startyear"].as<int>();
        item.startdate.month = start["startmonth"].as<int>();
        item.startdate.day = start["startday"].as<int>();
        item.enddate.year = end["endyear"].as<int>();
        item.enddate.month = end["endmonth"].as<int>();
        item.enddate.day = end["endday"].as<int>();
        item.init_times();
        my_info.config.queries.push_back(item);
    }
    
    std::cout << "Read configuration file, will now start curling...\n";
}