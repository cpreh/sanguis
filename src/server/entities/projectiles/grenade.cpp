#include "grenade.hpp"
#include "aoe_damage.hpp"
#include "../insert_parameters_center.hpp"
#include "../transfer_parameters.hpp"
#include "../property/from_float.hpp"
#include "../../damage/list.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/fire.hpp"
#include "../../collision/distance.hpp"
#include "../../environment/object.hpp"
#include "../../environment/load_context.hpp"
#include "../../../duration_second.hpp"
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional_impl.hpp>
#include <algorithm>

sanguis::server::entities::projectiles::grenade::grenade(
	sanguis::diff_clock const &_diff_clock,
	server::environment::load_context &_load_context,
	team::type const _team,
	damage::unit const _damage,
	server::radius const _aoe,
	server::vector const &_dest,
	server::direction const _direction
)
:
	aoe_projectile(
		_diff_clock,
		aoe_projectile_type::grenade,
		_team,
		entities::movement_speed(10),
		_load_context.entity_dim(
			FCPPT_TEXT("grenade")
		),
		projectiles::life_time(
			sanguis::duration_second(
				2.f
			)
		),
		indeterminate::no,
		_aoe,
		_direction
	),
	diff_clock_(_diff_clock),
	slowdown_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			fcppt::chrono::milliseconds(
				100
			)
		)
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
	entities::transfer_parameters const &_param
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

	entities::with_body::on_transfer(
		_param
	);
}

void
sanguis::server::entities::projectiles::grenade::do_damage(
	with_health &
)
{
}

void
sanguis::server::entities::projectiles::grenade::on_update()
{
	if(
		sge::timer::reset_when_expired(
			slowdown_timer_
		)
	)
		this->movement_speed().current(
			this->movement_speed().current()
			* 0.9f
		);
}

void
sanguis::server::entities::projectiles::grenade::on_remove()
{
	this->environment().insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				projectiles::aoe_damage
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
