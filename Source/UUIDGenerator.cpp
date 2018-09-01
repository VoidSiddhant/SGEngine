#include "UUIDGenerator.h"
#include <time.h>
#include <stdlib.h>
namespace SGEngine
{
	SGUUIDGenerator& SGUUIDGenerator::instance()
	{
		static SGUUIDGenerator* _instance = new SGUUIDGenerator();
		return *_instance;
	}

	SGUUIDGenerator::SGUUIDGenerator()
	{
		srand(time(NULL));
	}

	void SGUUIDGenerator::Create(long int& value)
	{
		value = rand();
	}
}