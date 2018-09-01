#ifndef _UUIDGen_H
#define _UUIDGen_H

namespace SGEngine
{
	class SGUUIDGenerator
	{
	public:
		static SGUUIDGenerator& instance();
		void Create(long int& value);
	private:
		SGUUIDGenerator();
		~SGUUIDGenerator() {}
	};
};
#endif _UUIDGen_H