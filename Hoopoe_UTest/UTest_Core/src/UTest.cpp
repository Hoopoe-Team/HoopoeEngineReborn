#include "UTest.hpp"

bool HoopoeEngine::UTest::Test()
{
	return true;
}

HoopoeEngine::UTest::UTest()
{
	if (Test())
	{
		spdlog::info("Welcome to spdlog!");
	}
}

HoopoeEngine::UTest::~UTest()
{

}