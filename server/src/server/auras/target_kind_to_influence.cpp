#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/auras/target_kind_to_influence.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::auras::influence
sanguis::server::auras::target_kind_to_influence(
	sanguis::server::auras::target_kind const _target_kind
)
{
	switch(
		_target_kind
	)
	{
	case sanguis::server::auras::target_kind::enemy:
		return
			sanguis::server::auras::influence::debuff;
	case sanguis::server::auras::target_kind::friend_:
		return
			sanguis::server::auras::influence::buff;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
