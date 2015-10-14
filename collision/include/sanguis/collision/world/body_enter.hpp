#ifndef SANGUIS_COLLISION_WORLD_BODY_ENTER_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_ENTER_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_enter_fwd.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <fcppt/reference_wrapper_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body_enter
{
public:
	body_enter(
		sanguis::collision::world::body_base &,
		sanguis::collision::world::ghost_base &,
		sanguis::collision::world::created
	);

	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_base &
	body() const;

	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::ghost_base &
	ghost() const;

	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::created
	created() const;
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

	sanguis::collision::world::created created_;
};

}
}
}

#endif
