#ifndef SANGUIS_COLLISION_WORLD_BODY_EXIT_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_EXIT_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_exit_fwd.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <fcppt/reference_wrapper_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body_exit
{
public:
	body_exit(
		sanguis::collision::world::body_base &,
		sanguis::collision::world::ghost_base &
	);

	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_base &
	body() const;

	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::ghost_base &
	ghost() const;
private:
	typedef
	fcppt::reference_wrapper<
		sanguis::collision::world::body_base
	>
	body_ref;

	body_ref body_;

	typedef
	fcppt::reference_wrapper<
		sanguis::collision::world::ghost_base
	>
	ghost_ref;

	ghost_ref ghost_;
};

}
}
}

#endif
