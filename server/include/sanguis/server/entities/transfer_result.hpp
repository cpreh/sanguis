#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_RESULT_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class transfer_result
{
public:
	transfer_result();

	explicit
	transfer_result(
		sanguis::collision::world::body_enter_container &&
	);

	sanguis::collision::world::body_enter_container const &
	body_enter() const;

	sanguis::collision::world::body_enter_container &&
	release_body_enter();
private:
	sanguis::collision::world::body_enter_container body_enter_;
};

}
}
}

#endif
