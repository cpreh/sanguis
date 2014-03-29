#include <sanguis/tools/libmergeimage/exception.hpp>
#include <sge/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


sanguis::tools::libmergeimage::exception::exception(
	fcppt::string const &_text
)
:
	sge::exception(
		_text
	)
{
}

sanguis::tools::libmergeimage::exception::exception(
	fcppt::assert_::information const &_information
)
:
	sge::exception(
		_information
	)
{
}
