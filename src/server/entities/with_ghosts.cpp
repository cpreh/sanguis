#include "with_ghosts.hpp"

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
		_ghost
	);
}

void
sanguis::server::entities::with_ghosts::on_transfer(
	collision::global_groups const &_groups,
	collision::create_parameters const &_params
)
{
	this->recreate_ghosts(
		_groups,
		_params
	);
}
