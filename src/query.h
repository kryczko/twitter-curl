#ifndef _QUERY_H_
#define _QUERY_H_

class Query {
public:
    std::string title;
    std::string query;
    std::string head;
    std::string body;
    Query(std::string t, std::string q) {
        this->title = t;
        this->query = q;
        this->head = "queries/" + t + "_head.out";
        this->body = "queries/" + t + "_body.out";
    }
};

#endif