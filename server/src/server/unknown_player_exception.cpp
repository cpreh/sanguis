#include <sanguis/exception.hpp>
#include <sanguis/server/unknown_player_exception.hpp>
#include <fcppt/text.hpp>


sanguis::server::unknown_player_exception::unknown_player_exception()
:
	sanguis::exception(
		FCPPT_TEXT("unknown player")
	)
{
}
