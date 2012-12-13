#ifndef BAD_CONVERSION_H
#define	BAD_CONVERSION_H

#include "General_exception.h"

/** \brief Wyjątek rzucany jeżeli nastąpiła błędna konwersja stringa na liczbę. */
class NumberFormatException : public General_exception {
public:

    NumberFormatException() : General_exception() {
    };

    NumberFormatException(std::string cause) : General_exception(cause) {
    };
};


#endif	/* BAD_CONVERSION_H */

