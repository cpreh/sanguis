#include <sanguis/exception.hpp>
#include <sge/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>


sanguis::exception::exception(
	fcppt::string const &_what
)
:
	sge::exception(
		FCPPT_TEXT("sanguis: ")
		+
		_what
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
