#include "with_ghosts.hpp"
#include "transfer_parameters.hpp"
#include "../collision/ghost.hpp"
#include "../collision/make_groups.hpp"
#include "../environment/object.hpp"
#include <sge/projectile/ghost/scoped.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
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

	BOOST_FOREACH(
		ghost_list::reference ghost,
		ghosts_
	)
		this->insert_ghost(
			ghost,
			_params.world(),
			_params.global_groups()
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
