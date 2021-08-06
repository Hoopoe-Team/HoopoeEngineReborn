#pragma once

#include "UTestBase.hpp"

namespace HoopoeEngine
{
    class UTest : public UTestBase
    {
    public:
        UTest();
        ~UTest();
    private:
        virtual bool Test();
    };
}