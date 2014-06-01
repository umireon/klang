#include <CppUTest/TestHarness.h>

#include <string>

#include "kobject.h"
#include "Binding.h"

#include "ast/AstCompound.h"
#include "ast/AstInteger.h"

#include "parser/ParseCompound.h"

TEST_GROUP(AstCompound)
{
    Binding binding;
    Binding *b;
    
    ParseCompound p;
    AstCompound *com;
    KObject *res;
    
    void setup()
    {
        b = &binding;
    }
    
    void teardown()
    {
        delete com;
        delete res;
    }
};

TEST(AstCompound, SingleStatement)
{
    std::string input("{1}");
    com = p.parse_compound(input.begin());
    
    res = com->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}
