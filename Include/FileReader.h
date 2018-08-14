#ifndef _FILE_READER_H
#define _FILE_READER_H

#include "SGUtil.h"
#include <cstring>
#include <sstream>
namespace SGEngine
{
class SGFileReader final
{
  public:
    SGFileReader(const char *filename);
    ~SGFileReader();

    std::string ReadFull();
    SG_UINT Size() const{
        std::ostringstream oss ;
        oss<<fileStream.rdbuf();
        return strlen(oss.str().c_str());
    }
  private:
    std::ifstream fileStream;
};
}; // namespace SGEngine

#endif