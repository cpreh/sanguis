#ifndef SANGUIS_COLLISION_WORLD_BODY_BASE_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_BASE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/symbol/class.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class FCPPT_SYMBOL_CLASS body_base
{
	FCPPT_NONMOVABLE(
		body_base
	);
protected:
	SANGUIS_COLLISION_SYMBOL
	body_base();
public:
	SANGUIS_COLLISION_SYMBOL
	virtual
	~body_base();

	virtual
	void
	center_changed(
		sanguis::collision::center
	) = 0;

	virtual
	void
	speed_changed(
		sanguis::collision::speed const &
	) = 0;

	[[nodiscard]]
	virtual
	boost::logic::tribool
	can_collide_with(
		sanguis::collision::world::body_base const &
	) const = 0;

	virtual
	void
	collision(
		sanguis::collision::world::body_base & // NOLINT(google-runtime-references)
	) = 0; // NOLINT(google-runtime-references)

	virtual
	void
	world_collision() = 0;
};

}
}
}

#endif
