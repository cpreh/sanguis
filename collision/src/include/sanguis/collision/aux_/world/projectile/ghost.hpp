#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_GHOST_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/aux_/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/world/body_callback.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/scoped.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace projectile
{

class ghost
:
	public sanguis::collision::world::ghost
{
	FCPPT_NONCOPYABLE(
		ghost
	);
public:
	ghost(
		sge::projectile::world &,
		sanguis::collision::aux_::world::projectile::global_groups const &,
		sanguis::collision::world::ghost_parameters const &
	);

	~ghost()
	override;
private:
	void
	center(
		sanguis::collision::center
	)
	override;

	template<
		typename SgeFunction
	>
	fcppt::signal::auto_connection
	make_connection(
		SgeFunction,
		sanguis::collision::world::body_callback const &
	);

	sge::projectile::ghost::object impl_;

	fcppt::signal::scoped_connection const
		collision_begin_connection_,
		collision_end_connection_;

	sge::projectile::ghost::scoped scoped_;
};

}
}
}
}
}

#endif
