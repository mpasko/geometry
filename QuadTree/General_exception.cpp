#include "General_exception.h"

using namespace std;

General_exception::General_exception() : exception() {
};

General_exception::General_exception(std::string cause) : cause(cause){
};

General_exception::~General_exception() throw(){
}

const char* General_exception::what() {
    return cause.c_str();
}

