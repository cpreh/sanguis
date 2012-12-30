#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_health
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONCOPYABLE(
		with_health
	);
public:
	void
	damage(
		sanguis::server::damage::unit,
		sanguis::server::damage::array const &
	);

	void
	kill();

	sanguis::server::entities::property::changeable &
	health();

	sanguis::server::entities::property::always_max &
	regeneration();

	sanguis::server::health const
	current_health() const;

	sanguis::server::health const
	max_health() const;
protected:
	with_health(
		sanguis::diff_clock const &,
		sanguis::server::health max,
		sanguis::server::damage::armor const &
	);

	~with_health();

	void
	on_update();
private:
	bool
	dead() const;

	void
	max_health_change(
		sanguis::server::entities::property::value
	);

	sanguis::server::damage::armor armor_;

	sanguis::server::entities::property::changeable health_;

	sanguis::server::entities::property::always_max regeneration_;

	sanguis::diff_timer regeneration_timer_;

	fcppt::signal::scoped_connection const max_health_change_;
};

}
}
}

#endif

