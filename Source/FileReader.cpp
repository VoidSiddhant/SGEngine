#include "FileReader.h"

namespace SGEngine
{
    SGFileReader::SGFileReader(const char *filename)
    {
        fileStream.open(filename);
    }

    std::string SGFileReader::ReadFull()
    {
        std::ostringstream oss;
        oss << fileStream.rdbuf();
        return oss.str();
    }

    SGFileReader::~SGFileReader()
    {
    }
} // namespace SGEngine