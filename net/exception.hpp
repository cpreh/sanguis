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
	exception(sge::string const &);
};
}
}

#endif // SANGUIS_NET_EXCEPTION_HPP_INCLUDED
