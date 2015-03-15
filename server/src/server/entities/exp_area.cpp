#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
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
#include <fcppt/algorithm/map_iteration_second.hpp>
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
		sanguis::server::collision::ghost{
			*this,
			sanguis::collision::world::ghost_group::target_player,
			sanguis::server::radius(
				2000.f // TODO
			)
		}
	);
}

sanguis::server::entities::exp_area::~exp_area()
{
}

void
sanguis::server::entities::exp_area::remove_from_game()
{
	fcppt::algorithm::map_iteration_second(
		player_links_,
		[](
			sanguis::server::entities::auto_weak_link const &_link
		)
		{
			return
				!_link.get();
		}
	);

	for(
		auto &player_link
		:
		player_links_
	)
		fcppt::cast::static_downcast<
			sanguis::server::entities::player &
		>(
			*player_link.second.get()
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
	return
		true;
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
sanguis::server::entities::exp_area::on_body_enter(
	sanguis::collision::world::body_base &_base,
	sanguis::collision::world::created
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
sanguis::server::entities::exp_area::on_body_exit(
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
