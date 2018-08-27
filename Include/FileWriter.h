#ifndef _LOGGER_H
#define _LOGGER_H

#include "SGUtil.h"

namespace SGEngine
{
	class SGFileWriter final
	{
	private :
		using manip = std::ostream& (*)(std::ostream&);  // catch this function signature std::endl
	public:
		SGFileWriter(const char* filename);
		void Close();
		~SGFileWriter();
		template<class T>
		SG_INLINE friend SGFileWriter& operator<<(SGFileWriter& write, const T& stream);
		SG_INLINE friend SGFileWriter& operator<<(SGFileWriter& write, manip manipulator);
	private:
		
		std::ofstream outFile;
	};
	template<class T>
	SG_INLINE SGFileWriter& operator<<(SGFileWriter& write,const T& stream)
	{
		write.outFile << stream;
		return write;
	}
	SG_INLINE SGFileWriter& operator<<(SGFileWriter& write, SGFileWriter::manip manipulator)
	{
		write.outFile << manipulator;
		return write;
	}

}
#endif // !_LOGGER_H
