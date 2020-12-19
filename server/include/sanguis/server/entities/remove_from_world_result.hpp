#ifndef SANGUIS_SERVER_ENTITIES_REMOVE_FROM_WORLD_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_REMOVE_FROM_WORLD_RESULT_HPP_INCLUDED

#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/server/entities/remove_from_world_result_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class remove_from_world_result
{
public:
	remove_from_world_result();

	explicit
	remove_from_world_result(
		sanguis::collision::world::body_exit_container &&
	);

	[[nodiscard]]
	sanguis::collision::world::body_exit_container const &
	body_exit() const;

	[[nodiscard]]
	sanguis::collision::world::body_exit_container &&
	release_body_exit();
private:
	sanguis::collision::world::body_exit_container body_exit_;
};

}
}
}

#endif
