#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_BODY_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_BODY_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/aux_/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
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

class body
:
	public sanguis::collision::world::body
{
	FCPPT_NONCOPYABLE(
		body
	);
public:
	explicit
	body(
		sanguis::collision::world::body_parameters const &
	);

	~body()
	override;

	void
	activate(
		sge::projectile::world &,
		sanguis::collision::aux_::world::projectile::global_groups const &
	);
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

	sanguis::collision::world::group_field const collision_groups_;

	fcppt::signal::scoped_connection const position_connection_;

	typedef
	fcppt::scoped_ptr<
		sge::projectile::body::scoped
	> scoped_scoped_ptr;

	scoped_scoped_ptr scoped_;
};

}
}
}
}
}

#endif
