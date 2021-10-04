#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_OBJECT_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_OBJECT_HPP_INCLUDED

#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/body_list_grid.hpp>
#include <sanguis/collision/impl/world/simple/ghost_fwd.hpp>
#include <sanguis/collision/impl/world/simple/ghost_result_fwd.hpp>
#include <sanguis/collision/world/body_collision_container.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost_fwd.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#include <sanguis/collision/world/update_result_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_std_hash.hpp>
#include <fcppt/enum/array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sanguis::collision::impl::world::simple
{

class object
:
	public sanguis::collision::world::object
{
	FCPPT_NONMOVABLE(
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
	[[nodiscard]]
	sanguis::collision::world::body_unique_ptr
	create_body(
		sanguis::collision::world::body_parameters const &
	)
	override;

	[[nodiscard]]
	sanguis::collision::world::body_enter_container
	activate_body(
		fcppt::reference<
			sanguis::collision::world::body
		>,
		sanguis::collision::world::created
	)
	override;

	[[nodiscard]]
	sanguis::collision::world::body_exit_container
	deactivate_body(
		fcppt::reference<
			sanguis::collision::world::body
		>
	)
	override;

	[[nodiscard]]
	sanguis::collision::world::ghost_unique_ptr
	create_ghost(
		sanguis::collision::world::ghost_parameters const &
	)
	override;

	[[nodiscard]]
	sanguis::collision::world::body_enter_container
	activate_ghost(
		fcppt::reference<
			sanguis::collision::world::ghost
		>
	)
	override;

	[[nodiscard]]
	sanguis::collision::world::body_exit_container
	deactivate_ghost(
		fcppt::reference<
			sanguis::collision::world::ghost
		>
	)
	override;

	[[nodiscard]]
	sanguis::collision::world::update_result
	update(
		sanguis::collision::duration
	)
	override;

	void
	move_bodies(
		sanguis::collision::duration
	);

	[[nodiscard]]
	sanguis::collision::world::body_collision_container
	body_collisions() const;

	[[nodiscard]]
	sanguis::collision::impl::world::simple::ghost_result
	update_ghosts();

	void
	remove_body(
		sanguis::collision::impl::world::simple::body & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	void
	remove_ghost(
		sanguis::collision::impl::world::simple::ghost & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	void
	move_body(
		fcppt::reference<
			sanguis::collision::impl::world::simple::body
		>
	);

	using
	body_reference
	=
	fcppt::reference<
		sanguis::collision::impl::world::simple::body
	>;

	using
	body_set
	=
	std::unordered_set<
		body_reference
	>;

	using
	body_set_array
	=
	fcppt::enum_::array<
		sanguis::collision::world::body_group,
		body_set
	>;

	using
	ghost_reference
	=
	fcppt::reference<
		sanguis::collision::impl::world::simple::ghost
	>;

	using
	ghost_set
	=
	std::unordered_set<
		ghost_reference
	>;

	using
	ghost_set_array
	=
	fcppt::enum_::array<
		sanguis::collision::world::ghost_group,
		ghost_set
	>;

	using
	body_list_grid_array
	=
	fcppt::enum_::array<
		sanguis::collision::world::body_group,
		sanguis::collision::impl::world::simple::body_list_grid
	>;

	fcppt::reference<
		sanguis::creator::grid const
	> const grid_;

	body_set_array body_sets_;

	ghost_set_array ghost_sets_;

	body_list_grid_array body_list_grids_;
};

}

#endif
