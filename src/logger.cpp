#include "logger.hpp"

template<typename T>
Logger & Logger::operator << (T const & object)
{
  std::ostringstream m_os;
  m_os << object;
  os += m_os.str();
  SaveToFile(m_os.str());
  return *this;
}

template<typename T, template<typename, typename...> class C, typename... Args>
Logger & Logger::operator << (C<T, Args...> const & objs)
{
  std::ostringstream m_os;
  m_os << "COLLECTION: ";
  for (auto const & obj : objs)
    m_os << objs << "; ";
  os += m_os.str();
  SaveToFile(m_os.str());
  return *this;
}

Logger & Logger::operator << (std::string const & str)
{
  std::ostringstream m_os;
  m_os << str;
  os += m_os.str();
  SaveToFile(m_os.str());
  return *this;
}

void Logger::SaveToFile(std::string str)
{
  std::ofstream f("log.txt", std::ios::app);
  if (f.is_open())
  {
    f << str;
    f.close();
  }
  else
  {
    std::cerr << "Error opening file" << std::endl;
    Log << std::string("Error opening file\n");
  }
}
