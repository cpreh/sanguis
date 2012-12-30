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

sanguis::server::collision::body_enter_callback const
sanguis::server::collision::ghost_base::body_enter_callback()
{
	return
		collision::body_enter_callback(
			std::bind(
				&ghost_base::collision_begin,
				this,
				std::placeholders::_1
			)
		);

}

sanguis::server::collision::body_exit_callback const
sanguis::server::collision::ghost_base::body_exit_callback()
{
	return
		collision::body_exit_callback(
			std::bind(
				&ghost_base::collision_end,
				this,
				std::placeholders::_1
			)
		);
}

void
sanguis::server::collision::ghost_base::collision_begin(
	collision::body_base &_body
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
	collision::body_base &_body
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
