#include <sanguis/entity_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_id.hpp>


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
