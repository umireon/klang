#include <string>
#include <sstream>

#include <boost/numeric/ublas/vector.hpp>

#include "KObject.h"

using namespace boost::numeric;

std::string KVector::to_s(void)
{
    std::ostringstream os;
    os << "[ ";
    
    ublas::vector<double>::iterator iter = vect.begin();
    
    while (iter != vect.end()) {
        os << *iter << " ";
        iter++;
    }
    
    os << "]";

    return std::string(os.str());
}
