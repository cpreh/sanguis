#include <sanguis/cheat_type.hpp>
#include <sanguis/server/cheat.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/entities/player.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sanguis::server::cheat(
	sanguis::server::entities::player &_player,
	sanguis::cheat_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::cheat_type::exp:
		_player.add_exp(
			sanguis::server::exp(
				100000.f
			)
		);
		return;
	case sanguis::cheat_type::kill:
		_player.kill();
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
