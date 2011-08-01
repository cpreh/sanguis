#include "rocket.hpp"
#include "aoe_damage.hpp"
#include "../insert_parameters_center.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/fire.hpp"
#include "../../damage/full.hpp"
#include "../../environment/object.hpp"
#include "../../environment/load_context.hpp"
#include "../../../duration_second.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::projectiles::rocket::rocket(
	sanguis::diff_clock const &_diff_clock,
	server::environment::load_context &_load_context,
	server::team::type const _team,
	damage::unit const _damage,
	server::radius const _aoe,
	server::direction const _direction
)
:
	aoe_projectile(
		_diff_clock,
		aoe_projectile_type::rocket,
		_team,
		entities::movement_speed(6),
		_load_context.entity_dim(
			FCPPT_TEXT("rocket")
		),
		projectiles::life_time(
			sanguis::duration_second(
				10.f
			)
		),
		indeterminate::no,
		_aoe,
		_direction
	),
	diff_clock_(
		_diff_clock
	),
	damage_(
		_damage
	)
{
}

sanguis::server::entities::projectiles::rocket::~rocket()
{
}

void
sanguis::server::entities::projectiles::rocket::do_damage(
	with_health &
)
{
	this->expire();
}

void
sanguis::server::entities::projectiles::rocket::on_remove()
{
	this->environment().insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				aoe_damage
			>(
				fcppt::cref(
					diff_clock_
				),
				this->team(),
				this->aoe(),
				damage_,
				1u,
				sanguis::duration_second(
					0.1f
				),
				damage::list(
					damage::fire = damage::full
				)
			)
		),
		entities::insert_parameters_center(
			this->center()
		)
	);
}
