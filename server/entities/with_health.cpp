#include "with_health.hpp"
#include <boost/bind.hpp>

void
sanguis::server::entities::with_health::damage(
	damage::unit const damage_,
	damage::array const &amounts_
)
{
	// TODO:
	
	if(
		dead()
	)
		on_die();
}

void
sanguis::server::entities::with_health::die()
{
	health().current(
		0
	);

	on_die();
}

sanguis::server::entities::property &
sanguis::server::entities::with_health::health()
{
	return health_;
}

sanguis::server::entities::property &
sanguis::server::entities::with_health::regeneration()
{
	return regeneration_;
}

sanguis::server::entities::with_health::with_health(
	health_type const max_health_,
	damage::armor const &armor_
)
:
	health_(
		max_health_
	),
	armor_(
		armor_
	),
	max_health_change_(
		health_.register_max_change_callback(
			boost::bind(
				&with_health::max_health_change,
				this,
				_1
			)
		)
	)
{}

void
sanguis::server::entities::with_health::on_update(
	time_type const time_
)
{
	health().add(
		regeneration().current() * time_
	);
}

bool
sanguis::server::entities::with_health::dead() const
{
	return health().current() < 0.405f; // LOL Warcraft III
}

bool
sanguis::server::entities::with_health::invulnerable() const
{
	return false;
}

void
sanguis::server::entities::with_health::max_health_change(
	property::value_type const value_
)
{
	environment()->max_health_changed(
		id(),
		value_
	);
}
