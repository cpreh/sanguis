#ifndef SANGUIS_COLLISION_WORLD_BODY_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/optional_mass_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::collision::world
{

class body
{
	FCPPT_NONMOVABLE(
		body
	);
protected:
	body();
public:
	virtual
	~body();

	virtual
	void
	center(
		sanguis::collision::center
	) = 0;

	[[nodiscard]]
	virtual
	sanguis::collision::center
	center() const = 0;

	virtual
	void
	speed(
		sanguis::collision::speed
	) = 0;

	[[nodiscard]]
	virtual
	sanguis::collision::speed
	speed() const = 0;

	[[nodiscard]]
	virtual
	sanguis::collision::radius
	radius() const = 0;

	[[nodiscard]]
	virtual
	sanguis::collision::optional_mass
	mass() const = 0;
};

}

#endif
