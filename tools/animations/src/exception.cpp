#include <sanguis/tools/animations/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/assert/make_message.hpp>


sanguis::tools::animations::exception::exception(
	fcppt::string const &_text
)
:
	fcppt::exception(
		_text
	)
{
}

sanguis::tools::animations::exception::exception(
	fcppt::assert_::information const &_information
)
:
	fcppt::exception(
		fcppt::assert_::make_message(
			_information
		)
	)
{
}
