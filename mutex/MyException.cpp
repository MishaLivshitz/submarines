#include "MyException.h"


MyException::MyException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line)
: m_file(_fileName)
, m_line(_line)
, m_func(_funcName)
, m_what(_err)
{

}

MyException::~MyException() NO_EXCEPT
{

}


std::string MyException::m_buff(1024,0);