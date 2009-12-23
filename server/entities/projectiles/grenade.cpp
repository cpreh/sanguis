#include "grenade.hpp"
#include "aoe_damage.hpp"
#include "../insert_parameters_pos.hpp"
#include "../property/from_float.hpp"
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
#include <fcppt/container/map_impl.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/millisecond.hpp>
#include <fcppt/text.hpp>
#include <sge/optional_impl.hpp>
#include <algorithm>

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
		entities::movement_speed(500),
		load_context_->entity_dim(
			FCPPT_TEXT("grenade")
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
		std::min(
			movement_speed().max(),
			property::from_float(
				collision::distance(
					param_.center(),
					dest_
				)
			)
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
			movement_speed().current()
			* property::value(
				9,
				10
			)
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
		insert_parameters_pos(
			center()
		)
	);
}
