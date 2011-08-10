#include "with_ghosts.hpp"
#include "transfer_parameters.hpp"
#include "../collision/ghost.hpp"
#include "../collision/make_groups.hpp"
#include "../environment/object.hpp"
#include <sge/projectile/ghost/scoped.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::entities::with_ghosts::with_ghosts()
:
	ghosts_(),
	scoped_ghosts_()
{
}

sanguis::server::entities::with_ghosts::~with_ghosts()
{
	FCPPT_ASSERT(
		scoped_ghosts_.empty()
	);
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

	ghosts_.back().center(
		this->center()
	);

	if(
		this->has_environment()
	)
		this->insert_ghost(
			ghosts_.back(),
			this->environment().collision_world(),
			this->environment().global_collision_groups()
		);
}

void
sanguis::server::entities::with_ghosts::on_transfer(
	entities::transfer_parameters const &_params
)
{
	scoped_ghosts_.clear();

	for(
		ghost_list::iterator ghost_it(
			ghosts_.begin()
		);
		ghost_it != ghosts_.end();
		++ghost_it
	)
		this->insert_ghost(
			*ghost_it,
			_params.world(),
			_params.global_groups()
		);

	this->update_center(
		_params.center()
	);
}

void
sanguis::server::entities::with_ghosts::on_destroy()
{
	scoped_ghosts_.clear();
}

void
sanguis::server::entities::with_ghosts::update_center(
	server::center const &_center
)
{
	for(
		ghost_list::iterator ghost_it(
			ghosts_.begin()
		);
		ghost_it != ghosts_.end();
		++ghost_it
	)
		ghost_it->center(
			_center
		);
}

void
sanguis::server::entities::with_ghosts::insert_ghost(
	collision::ghost &_ghost,
	sge::projectile::world &_world,
	collision::global_groups const &_global_groups
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		scoped_ghosts_,
		fcppt::make_unique_ptr<
			sge::projectile::ghost::scoped
		>(
			fcppt::ref(
				_world
			),
			fcppt::ref(
				_ghost.get()
			),
			collision::make_groups(
				_ghost.groups(),
				_global_groups
			)
		)
	);
}
