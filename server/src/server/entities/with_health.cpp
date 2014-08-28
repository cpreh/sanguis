#include <sanguis/diff_timer.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/initial_max.hpp>
#include <sanguis/server/entities/property/subtract.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_health::damage(
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::modified_array const &_amounts
)
{
	for(
		auto const index
		:
		fcppt::make_enum_range<
			sanguis::server::damage::type
		>()
	)
		sanguis::server::entities::property::subtract(
			health_,
			_damage.get()
			*
			_amounts[
				index
			].get()
			*
			(
				fcppt::literal<
					sanguis::server::damage::unit::value_type
				>(
					1
				)
				-
				armor_[
					index
				].get()
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
	return
		health_;
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_health::regeneration()
{
	return
		regeneration_;
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
	sanguis::server::health const _max_health,
	sanguis::server::regeneration const _regeneration,
	sanguis::server::damage::armor_array const &_armor
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::ifaces::with_health(),
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
		_regeneration.get()
	),
	regeneration_timer_(
		sanguis::diff_timer::parameters(
			this->diff_clock(),
			std::chrono::seconds(
				1
			)
		)
	),
	net_health_(
		this->diff_clock()
	),
	health_change_(
		health_.register_change_callback(
			std::bind(
				&sanguis::server::entities::with_health::health_change,
				this
			)
		)
	),
	max_health_change_(
		health_.register_max_change_callback(
			std::bind(
				&sanguis::server::entities::with_health::max_health_change,
				this
			)
		)
	)
{
}

sanguis::server::entities::with_health::~with_health()
{
}

void
sanguis::server::entities::with_health::update()
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

	if(
		net_health_.update()
	)
		this->environment()->health_changed(
			this->id(),
			this->current_health()
		);
}

bool
sanguis::server::entities::with_health::dead() const
{
	return
		health_.current() <= 0;
}

void
sanguis::server::entities::with_health::health_change()
{
	net_health_.set(
		this->current_health()
	);
}

void
sanguis::server::entities::with_health::max_health_change()
{
	this->environment()->max_health_changed(
		this->id(),
		this->max_health()
	);
}
