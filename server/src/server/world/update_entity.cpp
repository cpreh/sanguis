#include <sanguis/duration.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/entities/doodad_unique_ptr.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/world/update_entity.hpp>


sanguis::server::world::update_entity::update_entity(
	sanguis::duration const _elapsed_time
)
:
	elapsed_time_{
		_elapsed_time
	}
{
}

bool
sanguis::server::world::update_entity::operator()(
	sanguis::server::entities::unique_ptr const &_entity
) const
{
	return
		this->impl(
			_entity
		);
}

bool
sanguis::server::world::update_entity::operator()(
	sanguis::server::entities::doodad_unique_ptr const &_entity
) const
{
	return
		this->impl(
			_entity
		);
}

bool
sanguis::server::world::update_entity::operator()(
	sanguis::server::entities::with_id_unique_ptr const &_entity
) const
{
	return
		this->impl(
			_entity
		);
}

template<
	typename T
>
bool
sanguis::server::world::update_entity::impl(
	T const &_entity
) const
{
	_entity->tick(
		elapsed_time_
	);

	_entity->update();

	if(
		_entity->dead()
	)
	{
		_entity->remove();

		return
			true;
	}

	return
		false;
}
