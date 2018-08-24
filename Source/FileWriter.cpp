#include "FileWriter.h"

namespace SGEngine
{
	SGFileWriter::SGFileWriter(const char* filename)
	{
		outFile.open(filename);
	}

	void SGFileWriter::Close()
	{
		outFile.close();
	}

	SGFileWriter::~SGFileWriter()
	{
		outFile.close();
	}
}