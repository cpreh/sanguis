#include <sanguis/tiles/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tiles::exception::exception(
	fcppt::string &&_message
)
:
	fcppt::exception(
		FCPPT_TEXT("sanguis::tiles: ")
		+
		std::move(
			_message
		)
	)
{
}

sanguis::tiles::exception::exception(
	exception &&
)
noexcept
= default;

sanguis::tiles::exception::exception(
	exception const &
)
= default;

sanguis::tiles::exception &
sanguis::tiles::exception::operator=(
	exception &&
)
noexcept
= default;

sanguis::tiles::exception &
sanguis::tiles::exception::operator=(
	exception const &
)
= default;

sanguis::tiles::exception::~exception()
noexcept
= default;
