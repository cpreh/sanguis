#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_variate_decl.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/projectiles/scatter_create.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>
#include <fcppt/random/distribution/transform/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class scatter
:
	public sanguis::server::entities::projectiles::projectile
{
	FCPPT_NONCOPYABLE(
		scatter
	);
public:
	scatter(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::server::direction,
		sanguis::server::entities::projectiles::scatter_create const &
	);

	~scatter();
private:
	void
	update()
	override;

	void
	do_damage(
		sanguis::server::entities::with_health &
	)
	override;

	sanguis::server::entities::projectiles::scatter_create const create_;

	sanguis::diff_timer shoot_timer_;

	typedef
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			sanguis::server::angle
		>
	>
	angle_distribution;

	typedef
	sanguis::random_variate<
		angle_distribution
	>
	angle_rng;

	angle_rng angle_rng_;
};

}
}
}
}

#endif
