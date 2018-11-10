#include <sanguis/creator/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::creator::exception::exception(
	fcppt::string &&_message
)
:
	fcppt::exception(
		FCPPT_TEXT("creator: ")
		+
		std::move(
			_message
		)
	)
{
}

sanguis::creator::exception::exception(
	exception &&
)
= default;

sanguis::creator::exception::exception(
	exception const &
)
= default;

sanguis::creator::exception &
sanguis::creator::exception::operator=(
	exception &&
)
= default;

sanguis::creator::exception &
sanguis::creator::exception::operator=(
	exception const &
)
= default;

sanguis::creator::exception::~exception() noexcept
{
}
