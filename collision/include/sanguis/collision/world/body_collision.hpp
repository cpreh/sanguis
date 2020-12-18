#ifndef SANGUIS_COLLISION_WORLD_BODY_COLLISION_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_COLLISION_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_collision_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body_collision
{
public:
	using
	body_ref
	=
	fcppt::reference<
		sanguis::collision::world::body_base
	>;

	body_collision(
		body_ref,
		body_ref
	);

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_base &
	body1() const;

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_base &
	body2() const;
private:
	body_ref body1_;

	body_ref body2_;
};

}
}
}

#endif
