#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/initial_max.hpp>
#include <sanguis/server/entities/property/subtract.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_health::damage(
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::array const &_amounts
)
{
        for(
		sanguis::server::damage::array::size_type i = 0;
		i < _amounts.size();
		++i
	)
		sanguis::server::entities::property::subtract(
			health_,
			_damage.get()
			* _amounts[i].get() * (1 - armor_.get()[i].get())
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
		sanguis::server::health(
			health_.current()
		);
}

sanguis::server::health const
sanguis::server::entities::with_health::max_health() const
{
	return
		sanguis::server::health(
			health_.max()
		);
}

sanguis::server::entities::with_health::with_health(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::health const _max_health,
	sanguis::server::damage::armor const &_armor
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::entities::ifaces::with_links(),
	armor_(
		_armor
	),
	health_(
		sanguis::server::entities::property::initial_max(
			_max_health.get()
		)
	),
	regeneration_(
		0
	),
	regeneration_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::seconds(
				1
			)
		)
	),
	max_health_change_(
		health_.register_max_change_callback(
			std::bind(
				&sanguis::server::entities::with_health::max_health_change,
				this,
				std::placeholders::_1
			)
		)
	)
{
}

sanguis::server::entities::with_health::~with_health()
{
}

void
sanguis::server::entities::with_health::on_update()
{
	sanguis::server::entities::property::add(
		health_,
		sge::timer::elapsed_fractional_and_reset<
			sanguis::server::space_unit
		>(
			regeneration_timer_
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
	sanguis::server::entities::property::value const _value
)
{
	this->environment().max_health_changed(
		this->id(),
		sanguis::server::health(
			_value
		)
	);
}
