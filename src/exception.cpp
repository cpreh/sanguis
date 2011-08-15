#include "exception.hpp"
#include <fcppt/text.hpp>

sanguis::exception::exception(
	fcppt::string const &_what
)
:
	sge::exception(
		FCPPT_TEXT("sanguis: ")
		+ _what
	)
{
}

sanguis::exception::exception(
	fcppt::assert_::information const &_info
)
:
	sge::exception(
		_info
	)
{
}
