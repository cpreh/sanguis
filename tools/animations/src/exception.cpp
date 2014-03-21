#include <sanguis/tools/animations/exception.hpp>
#include <sge/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


sanguis::tools::animations::exception::exception(
	fcppt::string const &_text
)
:
	sge::exception(
		_text
	)
{
}

sanguis::tools::animations::exception::exception(
	fcppt::assert_::information const &_information
)
:
	sge::exception(
		_information
	)
{
}
