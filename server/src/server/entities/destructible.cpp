#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/load/model/destructible_path.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/destructible_type.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/server/add_destructible.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/destructible.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>


sanguis::server::entities::destructible::destructible(
	sanguis::creator::destructible_type const _type,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::health const _health,
	sanguis::server::damage::armor_array const &_armor,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
:
	sanguis::server::entities::with_body(
		_load_context.model_size(
			sanguis::load::model::destructible_path(
				_type
			)
		)
	),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_health(
		_health,
		sanguis::server::regeneration(
			0.f
		),
		_armor
	),
	sanguis::server::entities::with_links(),
	type_(
		_type
	),
	difficulty_(
		_difficulty
	)
{
}

sanguis::server::entities::destructible::~destructible()
{
}

void
sanguis::server::entities::destructible::update()
{
	sanguis::server::entities::with_body::update();

	sanguis::server::entities::with_health::update();
}

void
sanguis::server::entities::destructible::remove()
{
	if(
		this->environment()
	)
		this->environment()->pickup_chance(
			// TODO
			sanguis::server::pickup_probability(
				1.f
			),
			difficulty_,
			this->center()
		);
}

sanguis::server::team
sanguis::server::entities::destructible::team() const
{
	return
		sanguis::server::team::monsters;
}

sanguis::collision::world::body_group
sanguis::server::entities::destructible::collision_group() const
{
	return
		sanguis::collision::world::body_group::enemy;
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::destructible::add_message(
	sanguis::server::player_id
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_destructible(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::destructible_type{} =
					type_
			)
		);
}
