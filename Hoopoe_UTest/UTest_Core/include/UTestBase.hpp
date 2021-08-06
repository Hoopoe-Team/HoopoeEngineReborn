#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace HoopoeEngine
{
	class UTestBase
	{
	protected:

		virtual bool Test() { return false; };
		virtual void Complete() final;
		virtual void inComplete() final;
		void color();
	public:
		UTestBase();
		virtual ~UTestBase() {};
	};
}