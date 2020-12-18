#ifndef SANGUIS_COLLISION_WORLD_BODY_EXIT_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_EXIT_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_exit_fwd.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body_exit
{
public:
	using
	body_ref
	=
	fcppt::reference<
		sanguis::collision::world::body_base
	>;

	using
	ghost_ref
	=
	fcppt::reference<
		sanguis::collision::world::ghost_base
	>;

	body_exit(
		body_ref,
		ghost_ref
	);

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_base &
	body() const;

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::ghost_base &
	ghost() const;
private:
	body_ref body_;

	ghost_ref ghost_;
};

}
}
}

#endif
