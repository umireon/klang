#include <string>
#include <sstream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include "kobject/KMatrix.h"

using boost::numeric::ublas::matrix;
using boost::numeric::ublas::matrix_row;

std::string KMatrix::to_s(void)
{
    std::ostringstream os;
    os << "[" << std::endl;
    
    for (unsigned i = 0; i < mat.size1(); ++i) {
    	matrix_row<dmatrix> mr(mat, i);

    	for (unsigned j = 0; j < mr.size(); ++j) {
    		os << mr(j) << " ";
    	}
    	os << std::endl;
    }
    
    os << "]";

    return std::string(os.str());
}
