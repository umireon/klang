#include <igloo/igloo_alt.h>
using namespace igloo;

extern "C" int add(int, int);

int input(const char *str)
{
    Assert::Failure("策定中");
    return 0;
}

Describe(ProgramCalc)
{
    It(Adds)
    {
        Assert::That(input("2+3\n"), Equals(5));
    }
    It(Arith)
    {
        Assert::Failure("策定中");
    }

    It(DefineFunc)
    {
        Assert::Failure("策定中");
    }

    It(ExecFunc)
    {
        Assert::Failure("策定中");
    }

    It(AssignVar)
    {
        Assert::Failure("策定中");
    }
};

