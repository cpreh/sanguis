#ifndef SANGUIS_COLLISION_WORLD_BODY_EXIT_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_EXIT_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_exit_fwd.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>


namespace sanguis::collision::world
{

class body_exit
{
public:
	body_exit(
		sanguis::collision::world::body_base_ref,
		sanguis::collision::world::ghost_base_ref
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
	sanguis::collision::world::body_base_ref body_;

	sanguis::collision::world::ghost_base_ref ghost_;
};

}

#endif
