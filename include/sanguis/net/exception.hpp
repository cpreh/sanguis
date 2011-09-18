#ifndef SANGUIS_NET_EXCEPTION_HPP_INCLUDED
#define SANGUIS_NET_EXCEPTION_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace net
{

class exception
:
	public sanguis::exception
{
public:
	explicit exception(
		fcppt::string const &
	);
};

}
}

#endif
