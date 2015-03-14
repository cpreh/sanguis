#ifndef SANGUIS_SERVER_COLLISION_REMOVE_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_REMOVE_RESULT_HPP_INCLUDED

#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/server/collision/remove_result_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

class remove_result
{
public:
	explicit
	remove_result(
		sanguis::collision::world::body_exit_container &&
	);

	sanguis::collision::world::body_exit_container const &
	body_exit() const;

	sanguis::collision::world::body_exit_container &&
	release_body_exit();
private:
	sanguis::collision::world::body_exit_container body_exit_;
};

}
}
}

#endif
