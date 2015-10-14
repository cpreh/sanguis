#ifndef SANGUIS_COLLISION_WORLD_BODY_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/optional_mass_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body
{
	FCPPT_NONCOPYABLE(
		body
	);
protected:
	body();
public:
	virtual
	~body() = 0;

	virtual
	void
	center(
		sanguis::collision::center
	) = 0;

	virtual
	sanguis::collision::center
	center() const = 0;

	virtual
	void
	speed(
		sanguis::collision::speed
	) = 0;

	virtual
	sanguis::collision::speed
	speed() const = 0;

	virtual
	sanguis::collision::radius
	radius() const = 0;

	virtual
	sanguis::collision::optional_mass
	mass() const = 0;
};

}
}
}

#endif
