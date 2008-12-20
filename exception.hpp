#ifndef SANGUIS_EXCEPTION_HPP_INCLUDED
#define SANGUIS_EXCEPTION_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/string.hpp>

namespace sanguis
{

class exception : public sge::exception {
public:
	explicit exception(
		sge::string const &);
};

}

#endif
