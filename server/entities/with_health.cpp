#include "with_health.hpp"
#include "property/to_float.hpp"
#include "property/initial_max.hpp"
#include "../environment/object.hpp"
#include <tr1/functional>

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

sanguis::server::entities::property::changeable &
sanguis::server::entities::with_health::health()
{
	return health_;
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_health::regeneration()
{
	return regeneration_;
}

sanguis::server::health_type
sanguis::server::entities::with_health::current_health() const
{
	return property::to_float<
		server::health_type
	>(
		health_.current()
	);
}

sanguis::server::health_type
sanguis::server::entities::with_health::max_health() const
{
	return property::to_float<
		server::health_type
	>(
		health_.max()
	);
}

sanguis::server::entities::with_health::with_health(
	entities::health_type const max_health_,
	damage::armor const &armor_
)
:
	armor_(
		armor_
	),
	health_(
		property::initial_max(
			max_health_
		)
	),
	regeneration_(
		0
	),
	max_health_change_(
		health_.register_max_change_callback(
			std::tr1::bind(
				&with_health::max_health_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{}

void
sanguis::server::entities::with_health::on_update(
	time_type const time_
)
{
	health().current(
		health().current()
		+ regeneration().current() * time_
	);
}

void
sanguis::server::entities::with_health::on_die()
{
}

bool
sanguis::server::entities::with_health::dead() const
{
	return health_.current() < 0.405f; // LOL Warcraft III
}

bool
sanguis::server::entities::with_health::invulnerable() const
{
	return false;
}

void
sanguis::server::entities::with_health::max_health_change(
	property::value const value_
)
{
	environment()->max_health_changed(
		id(),
		property::to_float<
			server::health_type
		>(
			value_
		)
	);
}
