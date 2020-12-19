#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/random_variate_decl.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/projectiles/scatter_create.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>


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
	FCPPT_NONMOVABLE(
		scatter
	);
public:
	scatter(
		sanguis::random_generator_ref,
		sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
		sanguis::server::team,
		sanguis::server::direction,
		sanguis::server::entities::projectiles::scatter_create &&
	);

	~scatter()
	override;
private:
	void
	update()
	override;

	void
	do_damage(
		sanguis::server::entities::with_health & // NOLINT(google-runtime-references)
	) // NOLINT(google-runtime-references)
	override;

	sanguis::server::entities::projectiles::scatter_create const create_;

	sanguis::diff_timer shoot_timer_;

	using
	angle_distribution
	=
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			sanguis::server::angle
		>
	>;

	using
	angle_rng
	=
	sanguis::random_variate<
		angle_distribution
	>;

	angle_rng angle_rng_;
};

}
}
}
}

#endif
