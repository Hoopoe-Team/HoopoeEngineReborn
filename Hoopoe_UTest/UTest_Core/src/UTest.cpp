#include "UTest.hpp"

bool HoopoeEngine::UTest::Test()
{
	return true;
}

HoopoeEngine::UTest::UTest()
{
	color();
	if (Test())
	{
		Complete();
		inComplete();
	}
}

HoopoeEngine::UTest::~UTest() 
{

}