#include <sanguis/tools/animations/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/assert/make_message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::exception::exception(
	fcppt::string &&_text
)
:
	fcppt::exception(
		std::move(
			_text
		)
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

sanguis::tools::animations::exception::exception(
	exception &&
)
noexcept
= default;

sanguis::tools::animations::exception::exception(
	exception const &
)
= default;

sanguis::tools::animations::exception &
sanguis::tools::animations::exception::operator=(
	exception &&
)
noexcept
= default;

sanguis::tools::animations::exception &
sanguis::tools::animations::exception::operator=(
	exception const &
)
= default;

sanguis::tools::animations::exception::~exception()
noexcept
= default;
