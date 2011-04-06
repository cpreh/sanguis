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
				_damage.get()
				* _amounts[i].get() * (1 - armor_[i].get())
			)
		);
}

void
sanguis::server::entities::with_health::kill()
{
	health_.current(
		0
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

sanguis::server::health const
sanguis::server::entities::with_health::current_health() const
{
	return
		server::health(
			property::to_float<
				server::health::value_type
			>(
				health_.current()
			)
		);
}

sanguis::server::health const
sanguis::server::entities::with_health::max_health() const
{
	return
		server::health(
			property::to_float<
				server::health::value_type
			>(
				health_.max()
			)
		);
}

sanguis::server::entities::with_health::with_health(
	server::health const _max_health,
	damage::armor const &_armor
)
:
	armor_(
		_armor
	),
	health_(
		property::initial_max(
			_max_health.get()
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
{
}

sanguis::server::entities::with_health::~with_health()
{
}

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
		* this->regeneration().current()
	);
}

bool
sanguis::server::entities::with_health::dead() const
{
	return health_.current() <= 0;
}

void
sanguis::server::entities::with_health::max_health_change(
	property::value const _value
)
{
	this->environment().max_health_changed(
		this->id(),
		server::health(
			property::to_float<
				server::health::value_type
			>(
				_value
			)
		)
	);
}
