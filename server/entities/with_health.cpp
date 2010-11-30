#include "with_health.hpp"
#include "property/to_float.hpp"
#include "property/from_float.hpp"
#include "property/add.hpp"
#include "property/subtract.hpp"
#include "property/initial_max.hpp"
#include "../environment/object.hpp"
#include <fcppt/tr1/functional.hpp>

void
sanguis::server::entities::with_health::damage(
	damage::unit const _damage,
	damage::array const &_amounts
)
{
        for(
		damage::array::size_type i = 0;
		i < _amounts.size();
		++i
	)
		property::subtract(
			health_,
			property::from_float(
				_damage
				* _amounts[i] * (1 - armor_[i])
			)
		);
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
	entities::health_type const _max_health,
	damage::armor const &_armor
)
:
	armor_(
		_armor
	),
	health_(
		property::initial_max(
			_max_health
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
	time_type const _time
)
{
	entities::property::add(
		health_,
		property::from_float(
			_time
		)
		* regeneration().current()
	);
}

bool
sanguis::server::entities::with_health::dead() const
{
	return health_.current() <= 0;
}

bool
sanguis::server::entities::with_health::invulnerable() const
{
	return false;
}

void
sanguis::server::entities::with_health::max_health_change(
	property::value const _value
)
{
	environment()->max_health_changed(
		id(),
		property::to_float<
			server::health_type
		>(
			_value
		)
	);
}
