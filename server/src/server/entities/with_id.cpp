#include <sanguis/entity_id.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>


sanguis::server::entities::with_id::with_id(
	sanguis::entity_id const _id
)
:
	id_(
		_id
	)
{
}

sanguis::server::entities::with_id::~with_id()
{
}

sanguis::entity_id
sanguis::server::entities::with_id::id() const
{
	return
		id_;
}

void
sanguis::server::entities::with_id::transfer_to_world()
{
}

void
sanguis::server::entities::with_id::transfer_from_world()
{
	fcppt::optional::maybe_void(
		this->environment(),
		[
			this
		](
			fcppt::reference<
				sanguis::server::environment::object
			> const _environment
		)
		{
			_environment.get().request_transfer(
				this->id()
			);
		}
	);
}
