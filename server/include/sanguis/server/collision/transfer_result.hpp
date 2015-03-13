#ifndef SANGUIS_SERVER_COLLISION_TRANSFER_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TRANSFER_RESULT_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/collision/transfer_result_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

class transfer_result
{
public:
	explicit
	transfer_result(
		sanguis::collision::world::body_enter_container &&
	);

	sanguis::collision::world::body_enter_container const &
	body_enter() const;
private:
	sanguis::collision::world::body_enter_container body_enter_;
};

}
}
}

#endif
