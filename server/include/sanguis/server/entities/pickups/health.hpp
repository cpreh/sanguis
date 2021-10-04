#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED

#include <sanguis/server/health.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::pickups
{

class health
:
	public sanguis::server::entities::pickups::pickup
{
	FCPPT_NONMOVABLE(
		health
	);
public:
	health(
		sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
		sanguis::server::team,
		sanguis::server::health
	);

	~health()
	override;
private:
	[[nodiscard]]
	bool
	do_pickup(
		sanguis::server::entities::base &receiver // NOLINT(google-runtime-references)
	) // NOLINT(google-runtime-references)
	override;

	sanguis::server::health const amount_;
};

}

#endif
