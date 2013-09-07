#ifndef SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_BODY_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_BODY_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/aux/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/scoped.hpp>
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

class body
:
	public sanguis::collision::world::body
{
	FCPPT_NONCOPYABLE(
		body
	);
public:
	body(
		sge::projectile::world &,
		sanguis::collision::aux::world::projectile::global_groups const &,
		sanguis::collision::world::body_parameters const &
	);

	~body()
	override;
private:
	void
	center(
		sanguis::collision::center
	)
	override;

	sanguis::collision::center const
	center() const
	override;

	void
	speed(
		sanguis::collision::speed
	)
	override;

	sanguis::collision::speed const
	speed() const
	override;

	sge::projectile::body::object impl_;

	fcppt::signal::scoped_connection const position_connection_;

	sge::projectile::body::scoped const scoped_;
};

}
}
}
}
}

#endif
