#ifndef SANGUIS_COLLISION_WORLD_BODY_ENTER_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_ENTER_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_enter_fwd.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body_enter
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

	body_enter(
		body_ref,
		ghost_ref,
		sanguis::collision::world::created
	);

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_base &
	body() const;

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::ghost_base &
	ghost() const;

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::created
	created() const;
private:
	body_ref body_;

	ghost_ref ghost_;

	sanguis::collision::world::created created_;
};

}
}
}

#endif
