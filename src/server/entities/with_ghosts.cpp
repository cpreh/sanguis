#include "with_ghosts.hpp"
#include "../collision/ghost.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::with_ghosts::with_ghosts()
:
	ghosts_()
{
}

sanguis::server::entities::with_ghosts::~with_ghosts()
{
}

void
sanguis::server::entities::with_ghosts::add_ghost(
	collision::ghost_unique_ptr _ghost
)
{
	fcppt::container::ptr::push_back_unqiue_ptr(
		ghosts_,
		move(
			_ghost
		)
	);
}

void
sanguis::server::entities::with_ghosts::on_transfer(
	collision::create_parameters const &_params
)
{
	this->recreate_ghosts(
		_params
	);
}

void
sanguis::server::entities::with_ghosts::update_center(
	server::center const &_center
)
{
	BOOST_FOREACH(
		ghost_list::value_type &ghost,
		ghosts_
	)
		ghost.center(
			_center
		);
}
