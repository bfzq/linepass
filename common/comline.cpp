#include "comline.hpp"
#define MOVESPACE 1
ComLine::ComLine() 
{
  map = new std::map<std::string, std::string>;
}
ComLine::~ComLine()
{
  if (map)
  {
    delete map;
    map = nullptr;
  }
}

std::map<std::string, std::string>* 
ComLine::getKeyValue(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++) 
  {
    std::string t = std::string(argv[i]);
    int idx = t.find('=', 1);
    std::string key = t.substr(2, idx - MOVESPACE * 2);
    std::string value = t.substr(idx + MOVESPACE);
    if (!map) 
    {
      map = new std::map<std::string, std::string>;
    }
    map->insert(std::make_pair(key, value));
  }
  return map;
}


bool ComLine::haveHelp() 
{
  for(std::map<std::string, std::string>::iterator iter = map->begin();
  iter != map->end(); iter++) 
  {
    if(iter->first == "help") 
      return true;
  }
  return false;
}




void ComLine::printHelpInfo()
{
  std::cout << "  --listen-port  " << std::endl;
  std::cout << "  --pool-num  " << std::endl;
  std::cout << "  --mysql-port  " << std::endl;
  std::cout << "  --mysql-host  " << std::endl;
  std::cout << "  --mysql-user  " << std::endl;
  std::cout << "--mysql-passwd  " << std::endl;
  std::cout << "    --mysql-db  " << std::endl;
}

// find args address
int ComLine::findParamIndex(int argc, char**argv, std::string param) 
{
  for (int i = 1; i < argc; i++) 
  {
    std::string t = std::string(argv[i]);
    int idx = t.find('=', 1);
    std::string key = t.substr(2, idx - MOVESPACE * 2);
    if(key == param) return i;
  }
  return -1;
}
