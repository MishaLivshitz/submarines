#ifndef THREAD_CREATE_EXCEPTION_H
#define THREAD_CREATE_EXCEPTION_H

#include "MyException.h"

namespace advcpp{


class ThreadCreateException: private MyException
{

public:
    ThreadCreateException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line);
    const char* what();
    
    
};

inline ThreadCreateException::ThreadCreateException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line)
:MyException(_err,_fileName,_funcName,_line)
{

}


inline const char* ThreadCreateException::what()
{
    MyException::m_buff.clear();
    MyException::m_buff.append(m_what);
    MyException::m_buff.append(":\nin file: ");
    MyException::m_buff.append(m_file);
    MyException::m_buff.append("\nfunc: ");
    MyException::m_buff.append(m_func);
    MyException::m_buff.append("\nline: ");
    MyException::m_buff.append(m_line);
    return MyException::m_buff.c_str();
}

}

#endif