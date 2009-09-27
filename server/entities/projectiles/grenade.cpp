#include "grenade.hpp"
#include "aoe_damage.hpp"
#include "../property.hpp"
#include "../insert_parameters.hpp"
#include "../../collision/create_parameters.hpp"
#include "../../damage/list.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/fire.hpp"
#include "../../collision/distance.hpp"
#include "../../environment/object.hpp"
#include "../../environment/load_context.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/text.hpp>
#include <sge/optional_impl.hpp>

sanguis::server::entities::projectiles::grenade::grenade(
	server::environment::load_context_ptr const load_context_,
	team::type const team_,
	damage::unit const damage_,
	space_unit const aoe_,
	pos_type const &dest_,
	space_unit const direction_
)
:
	aoe_projectile(
		aoe_projectile_type::grenade,
		team_,
		server::movement_speed(0),
		load_context_->entity_dim(
			SGE_TEXT("grenade")
		),
		life_time(
			2
		),
		indeterminate::no,
		aoe_,
		direction_
	),
	diff_clock_(),
	slowdown_time(
		sge::time::millisecond(
			100
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	damage_(
		damage_
	),
	dest_(
		dest_
	)
{}

void
sanguis::server::entities::projectiles::grenade::on_transfer(
	collision::global_groups const &,
	collision::create_parameters const &param_
)
{
	movement_speed().current(
		collision::distance(
			param_.center(),
			dest_
		)
	);
}

void
sanguis::server::entities::projectiles::grenade::do_damage(
	with_health &
)
{}

void
sanguis::server::entities::projectiles::grenade::on_update(
	time_type const time
)
{
	diff_clock_.update(
		time
	);

	if(
		slowdown_time.update_b()
	)
		movement_speed().current(
			movement_speed().current() * static_cast<space_unit>(0.9)
		);
	
	projectile::on_update(
		time
	);
}

void
sanguis::server::entities::projectiles::grenade::on_die()
{
	environment()->insert(
		auto_ptr(
			new aoe_damage(
				team(),
				aoe(),
				damage_,
				1,
				static_cast<time_type>(0.1),
				damage::list(
					damage::piercing = damage::unit(0.5f)
				)(
					damage::fire = damage::unit(0.5f)
				)
			)
		),
		insert_parameters(
			center(),
			angle()
		)
	);
}
