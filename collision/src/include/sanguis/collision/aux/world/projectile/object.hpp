#ifndef SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_OBJECT_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_OBJECT_HPP_INCLUDED

#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux/world/projectile/global_groups.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#include <sge/projectile/world.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{
namespace world
{
namespace projectile
{

class object
:
	public sanguis::collision::world::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sanguis::collision::world::parameters const &
	);

	~object()
	override;
private:
	sanguis::collision::world::body_unique_ptr
	create_body(
		sanguis::collision::world::body_parameters const &
	)
	override;

	void
	activate_body(
		sanguis::collision::world::body &
	)
	override;

	sanguis::collision::world::ghost_unique_ptr
	create_ghost(
		sanguis::collision::world::ghost_parameters const &
	)
	override;

	void
	update(
		sanguis::collision::duration
	)
	override;

	sge::projectile::world impl_;

	fcppt::signal::scoped_connection const collision_connection_;

	sanguis::collision::aux::world::projectile::global_groups const global_groups_;
};

}
}
}
}
}

#endif
