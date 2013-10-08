#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/exp_area.hpp>
#include <sanguis/server/entities/is_type.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/cast/static_downcast_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::exp_area::exp_area(
	sanguis::server::exp const _exp
)
:
	sanguis::server::entities::with_ghosts(),
	sanguis::server::entities::center_ghost(),
	exp_(
		_exp
	),
	player_links_()
{
	this->add_ghost(
		fcppt::make_unique_ptr<
			sanguis::server::collision::ghost
		>(
			sanguis::collision::world::group_field{
				sanguis::collision::world::group::projectile_enemy
			},
			this->body_enter_callback(),
			this->body_exit_callback(),
			sanguis::server::radius(
				2000.f // TODO
			)
		)
	);
}

sanguis::server::entities::exp_area::~exp_area()
{
}

void
sanguis::server::entities::exp_area::on_remove()
{
	for(
		weak_link_map::iterator it(
			player_links_.begin()
		),
		next(
			it
		);
		it != player_links_.end();
		it = next
	)
	{
		++next;

		if(
			!it->second
		)
			player_links_.erase(
				it
			);
	}

	for(
		auto &player_link : player_links_
	)
		fcppt::cast::static_downcast<
			sanguis::server::entities::player &
		>(
			*player_link.second
		).add_exp(
			sanguis::server::exp(
				exp_.get()
				/
				fcppt::cast::int_to_float<
					sanguis::server::exp::value_type
				>(
					player_links_.size()
				)
			)
		);
}

bool
sanguis::server::entities::exp_area::dead() const
{
	return true;
}

boost::logic::tribool const
sanguis::server::entities::exp_area::can_collide_with(
	sanguis::collision::world::body_base const &_base
) const
{
	return
		sanguis::server::entities::is_type<
			sanguis::server::entities::player
		>(
			_base
		);
}

void
sanguis::server::entities::exp_area::body_enter(
	sanguis::collision::world::body_base &_base
)
{
	sanguis::server::entities::player &entity(
		fcppt::cast::static_downcast<
			sanguis::server::entities::player &
		>(
			_base
		)
	);

	player_links_.insert(
		std::make_pair(
			&entity,
			entity.link()
		)
	);
}

void
sanguis::server::entities::exp_area::body_exit(
	sanguis::collision::world::body_base &_base
)
{
	player_links_.erase(
		fcppt::cast::static_downcast_ptr<
			sanguis::server::entities::player *
		>(
			&_base
		)
	);
}
