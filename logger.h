/////////////////////////////////////////////////////////
///@brief 日志记录类
///
///@file Logger.h
///@author jayyao
///@date 2018-07-13
/////////////////////////////////////////////////////////
#ifndef __LOGGER_H
#define __LOGGER_H

#include <string>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#define LOG(fmt, args...) Logger::Instance().Log((char *)"%s:%d(%s): " fmt "\n", __FILE__, __LINE__, __FUNCTION__ , ## args);
#define LOGWithInfo(filename,linenum,function,fmt,args...) Logger::Instance().Log((char *)"%s:%d(%s): " fmt "\n", filename, linenum, function ,##args);

template <typename T>
T Argument(T value) noexcept
{
    return value;
}

template <typename T>
T const * Argument(std::basic_string<T> const & value) noexcept
{
    return value.c_str();
}

/////////////////////////////////////////////////////////
///@brief 日志记录类
///
/////////////////////////////////////////////////////////
class Logger {
public:
    static Logger& Instance() {
        static Logger logger;
        return logger;
    }

    /* more (non-static) functions here */
    template <typename ... Args>
    void Log(char *fmt , Args const & ... args){
        if(this->fp!=NULL){
            fprintf(this->fp,fmt,Argument(args) ...);
        }
        fflush(fp);
    }
private:
    std::string log_filename;
    FILE *fp = nullptr;
 
    // ctor hidden
    Logger(const std::string &filename="./err.log")
    :log_filename(filename) {
        fp = fopen(log_filename.c_str(),"a+");
    } 
    Logger(Logger const&);            // copy ctor hidden
    Logger& operator=(Logger const&); // assign op. hidden
    ~Logger(){
        if(this->fp!=NULL){
            fprintf(this->fp,"Logger Existing...\n");
        }
        fclose(fp);
        fp = nullptr;
    }                           // dtor hidden
};

// int main(){
//     LOG("%s=>%d","key",1);
//     return 0;
// }

#endif // __LOGGER_H