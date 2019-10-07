
#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>
#include <string.h>

#define LINE(L)	LINE_TO_STRING(L)
#define LINE_TO_STRING(L) #L
#define EXCEPTION(T,S)	T(S,__FILE__, __func__, LINE(__LINE__))
#define NO_EXCEPT throw()

class MyException: public std::exception
{

public:

    MyException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line);
    virtual ~MyException() NO_EXCEPT;
    virtual const char* what();

protected:
    std::string m_file;
    std::string m_line;
    std::string m_func;
    std::string m_what;
    static std::string m_buff; 

};

inline const char* MyException::what()
{
    m_buff.clear();
    m_buff.append(m_what);
    m_buff.append("in file: ");
    m_buff.append(m_file);
    m_buff.append("\nfunc: ");
    m_buff.append(m_func);
    m_buff.append("\nline: ");
    m_buff.append(m_line);
    m_buff.append("\n");
    
    return m_buff.c_str();
}

#endif
