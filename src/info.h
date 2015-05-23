#ifndef _INFO_H_
#define _INFO_H_

class Global_Info {
public:
    std::string username;
    std::string password;
    std::string hostname;
    std::string total;
    Global_Info(std::string u, std::string p, std::string h) {
        this->username = u;
        this->password = p;
        this->hostname = h;
        this->total = "https://" + u + ":" + p + "@" + h;
    }
};

#endif