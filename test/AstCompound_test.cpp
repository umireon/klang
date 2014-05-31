#include <CppUTest/TestHarness.h>

#include "kobject.h"
#include "ast/AstCompound.h"
#include "ast/AstInteger.h"
#include "parser/ParseCompound.h"

using std::string;

TEST_GROUP(AstCompound)
{
    Binding binding;
    Binding *b;
    
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
    ParseCompound p;
    com = p.parse_compound("{1}");
    
    res = com->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}
