#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_GLOBAL_GROUPS_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_GLOBAL_GROUPS_HPP_INCLUDED

#include <sanguis/collision/aux_/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <memory>
#include <fcppt/config/external_end.hpp>


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

class global_groups
{
	FCPPT_NONCOPYABLE(
		global_groups
	);
public:
	explicit
	global_groups(
		sge::projectile::world &
	);

	~global_groups();

	sge::projectile::group::object &
	body_group(
		sanguis::collision::world::body_group
	) const;

	sge::projectile::group::object &
	ghost_group(
		sanguis::collision::world::ghost_group
	) const;
private:
	typedef
	std::unique_ptr<
		sge::projectile::group::object
	>
	group_unique_ptr;

	typedef
	std::map<
		sanguis::collision::world::body_group,
		group_unique_ptr
	>
	body_group_map;

	typedef
	std::map<
		sanguis::collision::world::ghost_group,
		group_unique_ptr
	>
	ghost_group_map;

	// TODO: why are groups in projectile nonconst everywhere?
	mutable body_group_map body_groups_;

	mutable ghost_group_map ghost_groups_;
};

}
}
}
}
}

#endif
