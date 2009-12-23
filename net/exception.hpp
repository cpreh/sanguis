#ifndef SANGUIS_NET_EXCEPTION_HPP_INCLUDED
#define SANGUIS_NET_EXCEPTION_HPP_INCLUDED

#include <sge/exception.hpp>

namespace sanguis
{
namespace net
{
class exception : public sge::exception
{
public:
	explicit exception(fcppt::string const &);
};
}
}

#endif // SANGUIS_NET_EXCEPTION_HPP_INCLUDED
