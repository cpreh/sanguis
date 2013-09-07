#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::ghost_base::ghost_base()
{
}

sanguis::server::collision::ghost_base::~ghost_base()
{
}

sanguis::collision::world::body_enter_callback
sanguis::server::collision::ghost_base::body_enter_callback()
{
	return
		sanguis::collision::world::body_enter_callback(
			std::bind(
				&sanguis::server::collision::ghost_base::collision_begin,
				this,
				std::placeholders::_1
			)
		);

}

sanguis::collision::world::body_exit_callback
sanguis::server::collision::ghost_base::body_exit_callback()
{
	return
		sanguis::collision::world::body_exit_callback(
			std::bind(
				&sanguis::server::collision::ghost_base::collision_end,
				this,
				std::placeholders::_1
			)
		);
}

void
sanguis::server::collision::ghost_base::collision_begin(
	sanguis::collision::world::body_base &_body
)
{
	if(
		this->can_collide_with(
			_body
		)
	)
		this->body_enter(
			_body
		);
}

void
sanguis::server::collision::ghost_base::collision_end(
	sanguis::collision::world::body_base &_body
)
{
	if(
		this->can_collide_with(
			_body
		)
	)
		this->body_exit(
			_body
		);
}
