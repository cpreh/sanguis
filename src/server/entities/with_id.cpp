#include <sanguis/entity_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/environment/object.hpp>


sanguis::server::entities::with_id::with_id(
	sanguis::entity_id const _id
)
:
	sanguis::server::entities::base(),
	id_(
		_id
	)
{
}

sanguis::server::entities::with_id::~with_id()
{
}

sanguis::entity_id const
sanguis::server::entities::with_id::id() const
{
	return id_;
}

void
sanguis::server::entities::with_id::transfer_from_world()
{
	if(
		!this->has_environment()
	)
		return;

	this->environment().request_transfer(
		this->id()
	);
}
