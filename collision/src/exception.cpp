#include <sanguis/collision/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::exception::exception(
	fcppt::string &&_what
)
:
	fcppt::exception(
		FCPPT_TEXT("sanguis::coliision: ")
		+
		std::move(
			_what
		)
	)
{
}

sanguis::collision::exception::exception(
	exception &&
)
noexcept
= default;

sanguis::collision::exception::exception(
	exception const &
)
= default;

sanguis::collision::exception &
sanguis::collision::exception::operator=(
	exception &&
)
noexcept
= default;

sanguis::collision::exception &
sanguis::collision::exception::operator=(
	exception const &
)
= default;

sanguis::collision::exception::~exception()
noexcept
= default;
