#ifndef SANGUIS_EXCEPTION_HPP_INCLUDED
#define SANGUIS_EXCEPTION_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
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
	SANGUIS_COMMON_SYMBOL
	explicit
	exception(
		fcppt::string const &
	);

	SANGUIS_COMMON_SYMBOL
	explicit
	exception(
		fcppt::assert_::information const &
	);
};

}

#endif
