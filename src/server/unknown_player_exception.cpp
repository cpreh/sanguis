#include <sanguis/exception.hpp>
#include <sanguis/server/unknown_player_exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>


sanguis::server::unknown_player_exception::unknown_player_exception(
	fcppt::string const &_what
)
:
	sanguis::exception(
		FCPPT_TEXT("unknown player: ")
		+
		_what
	)
{
}

sanguis::server::unknown_player_exception::unknown_player_exception(
	fcppt::assert_::information const &_info
)
:
	sanguis::exception(
		_info
	)
{
}
