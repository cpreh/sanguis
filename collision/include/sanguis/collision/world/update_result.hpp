#ifndef SANGUIS_COLLISION_WORLD_UPDATE_RESULT_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_UPDATE_RESULT_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_collision_container.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/update_result_fwd.hpp>


namespace sanguis::collision::world
{

class update_result
{
public:
	update_result(
		sanguis::collision::world::body_enter_container &&,
		sanguis::collision::world::body_exit_container &&,
		sanguis::collision::world::body_collision_container &&
	);

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_enter_container const &
	body_enter() const;

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_exit_container const &
	body_exit() const;

	[[nodiscard]]
	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::world::body_collision_container const &
	body_collision() const;
private:
	sanguis::collision::world::body_enter_container body_enter_;

	sanguis::collision::world::body_exit_container body_exit_;

	sanguis::collision::world::body_collision_container body_collision_;
};

}

#endif
