#include <sanguis/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/assert/make_message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::exception::exception(
	fcppt::string &&_what
)
:
	fcppt::exception(
		FCPPT_TEXT("sanguis: ")
		+
		std::move(
			_what
		)
	)
{
}

sanguis::exception::exception(
	fcppt::assert_::information const &_info
)
:
	fcppt::exception(
		fcppt::assert_::make_message(
			_info
		)
	)
{
}

sanguis::exception::exception(
	exception &&
)
noexcept
= default;

sanguis::exception::exception(
	exception const &
)
= default;

sanguis::exception &
sanguis::exception::operator=(
	exception &&
)
noexcept
= default;

sanguis::exception &
sanguis::exception::operator=(
	exception const &
)
= default;

sanguis::exception::~exception()
noexcept
= default;
