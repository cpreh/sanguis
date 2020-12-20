#include <sanguis/duration.hpp>
#include <sanguis/server/collision/body_exit.hpp>
#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/entities/doodad_unique_ptr.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/simple_unique_ptr.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/world/update_entity.hpp>
#include <fcppt/algorithm/update_action.hpp>


sanguis::server::world::update_entity::update_entity(
	sanguis::duration const _elapsed_time
)
:
	elapsed_time_{
		_elapsed_time
	}
{
}

fcppt::algorithm::update_action
sanguis::server::world::update_entity::operator()(
	sanguis::server::entities::simple_unique_ptr const &_entity
) const
{
	return
		this->impl(
			_entity
		);
}

fcppt::algorithm::update_action
sanguis::server::world::update_entity::operator()(
	sanguis::server::entities::doodad_unique_ptr const &_entity
) const
{
	return
		this->impl(
			_entity
		);
}

fcppt::algorithm::update_action
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
fcppt::algorithm::update_action
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
		_entity->remove_from_game();

		sanguis::server::collision::body_exit(
			_entity->remove_from_world().body_exit()
		);

		return
			fcppt::algorithm::update_action::remove;
	}

	return
		fcppt::algorithm::update_action::keep;
}
