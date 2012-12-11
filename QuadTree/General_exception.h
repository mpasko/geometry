#ifndef GENERAL_EXCEPTION_H
#define	GENERAL_EXCEPTION_H

#include <exception>
#include <string>

/** \brief Klasa opisująca dowolny wyjątek, pozwala na podanie opisu przyczyny rzucenia wyjaku w kostruktorze. */
class General_exception : public std::exception {
public:
    General_exception();
    General_exception(std::string cause);
    ~General_exception() throw();
    const char* what();
private:
    std::string cause;
};

#endif	/* GENERAL_EXCEPTION_H */

