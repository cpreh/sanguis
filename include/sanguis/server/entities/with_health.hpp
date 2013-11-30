#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/regeneration_fwd.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/net/health.hpp>
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
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_id,
	public virtual sanguis::server::entities::ifaces::with_links
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
		sanguis::server::health,
		sanguis::server::regeneration,
		sanguis::server::damage::armor const &
	);

	~with_health();

	void
	update()
	override;
private:
	bool
	dead() const
	override;

	void
	health_change();

	void
	max_health_change();

	sanguis::server::damage::armor armor_;

	sanguis::server::entities::property::changeable health_;

	sanguis::server::entities::property::always_max regeneration_;

	sanguis::diff_timer regeneration_timer_;

	sanguis::server::net::health net_health_;

	fcppt::signal::scoped_connection const health_change_;

	fcppt::signal::scoped_connection const max_health_change_;
};

}
}
}

#endif

