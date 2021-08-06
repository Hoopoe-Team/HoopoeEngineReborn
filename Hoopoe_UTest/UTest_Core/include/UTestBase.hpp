#pragma once

#include <spdlog/spdlog.h>

namespace HoopoeEngine
{

	class UTestBase
	{
	private:
		virtual bool Test();
	public:
		UTestBase();
		~UTestBase() {};
	};
}