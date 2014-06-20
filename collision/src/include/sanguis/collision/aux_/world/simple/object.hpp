#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_OBJECT_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_OBJECT_HPP_INCLUDED

#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux_/world/simple/body.hpp>
#include <sanguis/collision/aux_/world/simple/body_list_grid.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_fwd.hpp>
#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/enum_array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace simple
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

	void
	remove_body(
		sanguis::collision::aux_::world::simple::body &
	);

	void
	remove_ghost(
		sanguis::collision::aux_::world::simple::ghost &
	);

	void
	move_body(
		sanguis::collision::aux_::world::simple::body &
	);

public:
	// TODO
	typedef
	std::unordered_set<
		sanguis::collision::aux_::world::simple::body *
	>
	body_set;

	typedef
	fcppt::container::enum_array<
		sanguis::collision::world::group,
		body_set
	>
	body_set_array;

	typedef
	std::unordered_set<
		sanguis::collision::aux_::world::simple::ghost *
	>
	ghost_set;

	typedef
	fcppt::container::enum_array<
		sanguis::collision::world::group,
		ghost_set
	>
	ghost_set_array;

	typedef
	fcppt::container::enum_array<
		sanguis::collision::world::group,
		sanguis::collision::aux_::world::simple::body_list_grid
	>
	body_list_grid_array;
private:
	sanguis::collision::world::body_collision_callback const body_collision_callback_;

	body_set_array body_sets_;

	ghost_set_array ghost_sets_;

	body_list_grid_array body_list_grids_;
};

}
}
}
}
}

#endif
