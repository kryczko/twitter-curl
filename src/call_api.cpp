#include "curl-memory.h"
#include "info.h"
#include <vector>
#include <cstdlib>

void do_work(Item* q, Global_Info* my_info) {
    while (difftime(q->t_end, q->t_current) > 0) {
      if (!curl_string(q, my_info)) { 
            std::cout << "#####\nERROR: Could not curl the query with title: " << q->title << ". Exiting...\n#####\n"; 
            exit(-1);
        }
        q->update_current_time(); 
    }
}

void call_api(Global_Info& my_info) { 
    //Global_Info* my_info_pointer = &my_info;
    //std::vector<std::thread> my_threads;
    for (int i = 0; i < my_info.config.queries.size(); i ++) {
        //my_threads.push_back(std::thread (do_work, &q, &my_info));
        Item& q = my_info.config.queries[i];
        do_work(&q, &my_info);
    }
    
    /*for (auto& t : my_threads) {
        t.join();
    }*/
}