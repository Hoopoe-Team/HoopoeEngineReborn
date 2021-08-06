#include "UTestBase.hpp"

void HoopoeEngine::UTestBase::color()
{
	spdlog::set_pattern("%^[UTEST]%$ %v");
}

void HoopoeEngine::UTestBase::Complete()
{
	spdlog::info("COMPLETE");
}

void HoopoeEngine::UTestBase::inComplete()
{
	spdlog::critical("INCOMPLETE");
}

HoopoeEngine::UTestBase::UTestBase()
{
    
}