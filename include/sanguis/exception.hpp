#ifndef SANGUIS_EXCEPTION_HPP_INCLUDED
#define SANGUIS_EXCEPTION_HPP_INCLUDED

#include <sge/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace sanguis
{

class exception
:
	public sge::exception
{
public:
	explicit
	exception(
		fcppt::string const &
	);

	explicit
	exception(
		fcppt::assert_::information const &
	);
};

}

#endif
