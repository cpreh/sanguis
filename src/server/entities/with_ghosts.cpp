#include "with_ghosts.hpp"
#include "ghost_parameters.hpp"
#include "transfer_parameters.hpp"
#include "../collision/create_parameters.hpp"
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
	fcppt::container::ptr::push_back_unique_ptr(
		ghosts_,
		move(
			_ghost
		)
	);
}

void
sanguis::server::entities::with_ghosts::on_transfer(
	entities::transfer_parameters const &_params
)
{
	this->recreate_ghosts(
		entities::ghost_parameters(
			_params.create_parameters().world(),
			_params.create_parameters().global_groups(),
			_params.create_parameters().center()
		)
	);
}

void
sanguis::server::entities::with_ghosts::update_center(
	server::center const &_center
)
{
	BOOST_FOREACH(
		ghost_list::reference ghost,
		ghosts_
	)
		ghost.center(
			_center
		);
}

void
sanguis::server::entities::with_ghosts::recreate_ghosts(
	entities::ghost_parameters const &
)
{
}
