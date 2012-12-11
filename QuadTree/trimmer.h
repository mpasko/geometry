/*
 * \brief metody do obcinania białych znaków w stringach
 */

/* 
 * File:   trimmer.h
 * Author: marcin
 *
 * Created on November 30, 2012, 10:58 PM
 */

#ifndef TRIMMER_H
#define	TRIMMER_H

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

#endif	/* TRIMMER_H */

