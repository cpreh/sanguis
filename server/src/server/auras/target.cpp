#include <sanguis/optional_aura_type.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/target.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/auras/target_kind_to_influence.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>


sanguis::server::auras::target::target(
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::auras::target_kind const _kind,
	sanguis::server::add_target_callback const &_add_target,
	sanguis::server::remove_target_callback const &_remove_target
)
:
	sanguis::server::auras::aura(
		_radius,
		_team,
		sanguis::server::auras::target_kind_to_influence(
			_kind
		)
	),
	add_target_(
		_add_target
	),
	remove_target_(
		_remove_target
	)
{
}

sanguis::server::auras::target::~target()
{
}

sanguis::optional_aura_type const
sanguis::server::auras::target::type() const
{
	return
		sanguis::optional_aura_type();
}

void
sanguis::server::auras::target::enter(
	sanguis::server::entities::with_body &_target
)
{
	add_target_.get()(
		_target
	);
}

void
sanguis::server::auras::target::leave(
	sanguis::server::entities::with_body &_target
)
{
	remove_target_.get()(
		_target
	);
}
