#ifndef SANGUIS_SERVER_ENTITIES_REMOVE_FROM_WORLD_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_REMOVE_FROM_WORLD_RESULT_HPP_INCLUDED

#include <sanguis/server/collision/remove_result.hpp>
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
		sanguis::server::collision::remove_result &&
	);

	sanguis::server::collision::remove_result const &
	collision_result() const;

	sanguis::server::collision::remove_result &&
	release_collision_result();
private:
	sanguis::server::collision::remove_result collision_result_;
};

}
}
}

#endif
