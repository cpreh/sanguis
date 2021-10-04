#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_RESULT_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>


namespace sanguis::server::entities
{

class transfer_result
{
public:
	transfer_result();

	explicit
	transfer_result(
		sanguis::collision::world::body_enter_container &&
	);

	[[nodiscard]]
	sanguis::collision::world::body_enter_container const &
	body_enter() const;

	[[nodiscard]]
	sanguis::collision::world::body_enter_container &&
	release_body_enter();
private:
	sanguis::collision::world::body_enter_container body_enter_;
};

}

#endif
