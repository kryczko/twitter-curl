#include "curl.h"
#include "info.h"

void call_api(Global_Info& my_info) { 
    for (auto& q : my_info.config.queries) {
        while (std::difftime(q.t_end, q.t_current) > 0) {
          if (!curl(q, my_info)) { 
                std::cout << "#####\nERROR: Could not curl the query with title: " << q.title << ". Exiting...\n#####\n"; 
                exit(-1);
            }
            q.update_current_time(); 
        }
    }
}