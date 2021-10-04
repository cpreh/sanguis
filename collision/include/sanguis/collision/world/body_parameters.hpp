#ifndef SANGUIS_COLLISION_WORLD_BODY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/log_fwd.hpp>
#include <sanguis/collision/optional_mass.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sanguis::collision::world
{

class body_parameters
{
public:
	SANGUIS_COLLISION_SYMBOL
	body_parameters(
		sanguis::collision::log const &,
		sanguis::collision::center,
		sanguis::collision::speed,
		sanguis::collision::radius,
		sanguis::collision::optional_mass,
		sanguis::collision::world::body_group,
		sanguis::collision::world::body_base_ref
	);

	[[nodiscard]]
	fcppt::log::object &
	log() const;

	[[nodiscard]]
	sanguis::collision::center
	center() const;

	[[nodiscard]]
	sanguis::collision::speed
	speed() const;

	[[nodiscard]]
	sanguis::collision::radius
	radius() const;

	[[nodiscard]]
	sanguis::collision::optional_mass
	mass() const;

	[[nodiscard]]
	sanguis::collision::world::body_group
	collision_group() const;

	[[nodiscard]]
	sanguis::collision::world::body_base &
	body_base() const;
private:
	fcppt::reference<
		fcppt::log::object
	> log_;

	sanguis::collision::center center_;

	sanguis::collision::speed speed_;

	sanguis::collision::radius radius_;

	sanguis::collision::optional_mass mass_;

	sanguis::collision::world::body_group collision_group_;

	sanguis::collision::world::body_base_ref body_base_;
};

}

#endif
