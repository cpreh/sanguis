#include <sanguis/aura_type.hpp>
#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/collision_group.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/create_callback.hpp>
#include <sanguis/server/buffs/optional_unique_ptr.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>


sanguis::server::auras::buff::buff(
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::aura_type const _aura_type,
	sanguis::server::auras::influence const _influence,
	sanguis::server::buffs::create_callback const &_create_callback
)
:
	sanguis::server::auras::aura(
		_radius,
		sanguis::server::auras::collision_group(
			_team,
			_influence
		)
	),
	aura_type_(
		_aura_type
	),
	create_callback_(
		_create_callback
	),
	provider_()
{
}

sanguis::server::auras::buff::~buff()
{
}

sanguis::optional_aura_type const
sanguis::server::auras::buff::type() const
{
	return
		sanguis::optional_aura_type(
			aura_type_
		);
}

void
sanguis::server::auras::buff::enter(
	sanguis::server::entities::with_body &_entity,
	sanguis::collision::world::created
)
{
	sanguis::server::buffs::optional_unique_ptr new_buff(
		create_callback_(
			_entity
		)
	);

	if(
		new_buff
	)
		provider_.add(
			dynamic_cast<
				sanguis::server::entities::with_buffs &
			>(
				_entity
			),
			std::move(
				*new_buff
			)
		);
}

void
sanguis::server::auras::buff::leave(
	sanguis::server::entities::with_body &_entity
)
{
	provider_.remove(
		dynamic_cast<
			sanguis::server::entities::with_buffs &
		>(
			_entity
		)
	);
}
