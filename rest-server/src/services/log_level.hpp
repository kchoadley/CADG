// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

namespace cadg_rest {
struct LogLevel {
    static const int ALL    = 0;
    static const int DEBUG  = 1;
    static const int INFO   = 2;
    static const int WARN   = 3;
    static const int ERR    = 4;
    static const int FATAL  = 5;
    static const int OFF    = 6;
};
}
#endif // LOG_LEVEL_H
