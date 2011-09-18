#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
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
	public virtual base
{
	FCPPT_NONCOPYABLE(
		with_health
	);
public:
	void
	damage(
		damage::unit,
		damage::array const &
	);

	void
	kill();

	property::changeable &
	health();

	property::always_max &
	regeneration();

	server::health const
	current_health() const;

	server::health const
	max_health() const;
protected:
	with_health(
		sanguis::diff_clock const &,
		server::health max,
		damage::armor const &
	);

	~with_health();

	void
	on_update();
private:
	bool
	dead() const;

	void
	max_health_change(
		property::value
	);

	damage::armor armor_;

	property::changeable health_;

	property::always_max regeneration_;

	sanguis::diff_timer regeneration_timer_;

	fcppt::signal::scoped_connection const max_health_change_;
};

}
}
}

#endif

