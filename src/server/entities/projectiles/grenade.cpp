#include "grenade.hpp"
#include "aoe_damage.hpp"
#include "../insert_parameters_center.hpp"
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
#include <sge/time/millisecond.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional_impl.hpp>
#include <algorithm>

sanguis::server::entities::projectiles::grenade::grenade(
	server::environment::load_context &_load_context,
	team::type const _team,
	damage::unit const _damage,
	server::radius const _aoe,
	server::vector const &_dest,
	server::direction const _direction
)
:
	aoe_projectile(
		aoe_projectile_type::grenade,
		_team,
		entities::movement_speed(500),
		_load_context.entity_dim(
			FCPPT_TEXT("grenade")
		),
		life_time(
			2
		),
		indeterminate::no,
		_aoe,
		_direction
	),
	diff_clock_(),
	slowdown_time_(
		sge::time::millisecond(
			100
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	damage_(
		_damage
	),
	dest_(
		_dest
	)
{
}

sanguis::server::entities::projectiles::grenade::~grenade()
{
}

void
sanguis::server::entities::projectiles::grenade::on_transfer(
	collision::global_groups const &,
	collision::create_parameters const &_param
)
{
	this->movement_speed().current(
		std::min(
			this->movement_speed().max(),
			property::from_float(
				collision::distance(
					_param.center().get(),
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
{
}

void
sanguis::server::entities::projectiles::grenade::on_update(
	time_type const _time
)
{
	diff_clock_.update(
		_time
	);

	if(
		slowdown_time_.update_b()
	)
		this->movement_speed().current(
			this->movement_speed().current()
			* 0.9f
		);
	
	projectile::on_update(
		_time
	);
}

void
sanguis::server::entities::projectiles::grenade::on_die()
{
	this->environment().insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				aoe_damage
			>(
				this->team(),
				this->aoe(),
				damage_,
				1u,
				static_cast<time_type>(0.1),
				damage::list(
					damage::piercing = damage::unit(0.5f)
				)(
					damage::fire = damage::unit(0.5f)
				)
			)
		),
		entities::insert_parameters_center(
			this->center()
		)
	);
}
