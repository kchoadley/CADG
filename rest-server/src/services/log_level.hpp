// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

namespace cadg_rest {
enum class LogLevel {
    ALL   = 0,
    DEBUG = 1,
    INFO  = 2,
    WARN  = 3,
    ERR   = 4,
    FATAL = 5,
    OFF   = 6
};
}
#endif // LOG_LEVEL_H
