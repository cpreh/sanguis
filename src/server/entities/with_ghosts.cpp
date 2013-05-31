#include <sanguis/server/center.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/ghost_unique_ptr.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/collision/make_groups.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/ghost/scoped.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_ghosts::with_ghosts()
:
	sanguis::server::entities::base(),
	ghosts_(),
	scoped_ghosts_()
{
}

sanguis::server::entities::with_ghosts::~with_ghosts()
{
	FCPPT_ASSERT_PRE(
		scoped_ghosts_.empty()
	);
}

void
sanguis::server::entities::with_ghosts::add_ghost(
	sanguis::server::collision::ghost_unique_ptr &&_ghost
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		ghosts_,
		std::move(
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

bool
sanguis::server::entities::with_ghosts::on_transfer(
	sanguis::server::entities::transfer_parameters const &_params
)
{
	scoped_ghosts_.clear();

	for(
		auto &ghost : ghosts_
	)
		this->insert_ghost(
			ghost,
			_params.world(),
			_params.global_groups()
		);

	this->update_center(
		_params.center()
	);

	return true;
}

void
sanguis::server::entities::with_ghosts::on_destroy()
{
	scoped_ghosts_.clear();
}

void
sanguis::server::entities::with_ghosts::update_center(
	sanguis::server::center const &_center
)
{
	for(
		auto &ghost : ghosts_
	)
		ghost.center(
			_center
		);
}

void
sanguis::server::entities::with_ghosts::insert_ghost(
	sanguis::server::collision::ghost &_ghost,
	sge::projectile::world &_world,
	sanguis::server::collision::global_groups const &_global_groups
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		scoped_ghosts_,
		fcppt::make_unique_ptr<
			sge::projectile::ghost::scoped
		>(
			_world,
			_ghost.get(),
			sanguis::server::collision::make_groups(
				_ghost.groups(),
				_global_groups
			)
		)
	);
}
