#include <sanguis/entity_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/maybe_void.hpp>


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
	return
		id_;
}

void
sanguis::server::entities::with_id::transfer_from_world()
{
	fcppt::maybe_void(
		this->environment(),
		[
			this
		](
			sanguis::server::environment::object &_environment
		)
		{
			_environment.request_transfer(
				this->id()
			);
		}
	);
}
