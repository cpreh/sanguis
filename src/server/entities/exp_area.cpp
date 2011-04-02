#include "exp_area.hpp"
#include "player.hpp"
#include "auto_weak_link.hpp"
#include "../../messages/base.hpp"
#include <fcppt/container/map_impl.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::exp_area::exp_area(
	server::exp const _exp
)
:
	exp_(_exp),
	player_links_()
{
}

sanguis::server::entities::exp_area::~exp_area()
{
}

void
sanguis::server::entities::exp_area::recreate_ghosts(
	entities::ghost_parameters const &_params
)
{
#if 0
	with_ghosts::add_ghost(
		fcppt::make_unique_ptr<
			collision::circle_ghost
		>(
			collision::ghost_parameters(
				_params.world(),
				_params.global_groups(),
				_params.center()
		)
	);
	return static_cast<space_unit>(2000); // TODO!
#endif
}

void
sanguis::server::entities::exp_area::on_die()
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

	BOOST_FOREACH(
		weak_link_map::reference ref,
		player_links_
	)
		dynamic_cast<
			player &
		>(
			*ref.second
		).add_exp(
			server::exp(
				exp_.get()
				/
				static_cast<
					exp::value_type
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

sanguis::messages::auto_ptr
sanguis::server::entities::exp_area::add_message(
	player_id const
) const
{
	return messages::auto_ptr(); // TODO: get rid of this
}

sanguis::entity_type::type
sanguis::server::entities::exp_area::type() const
{
	return entity_type::projectile; // FIXME
}

sanguis::server::team::type
sanguis::server::entities::exp_area::team() const
{
	return team::monsters; // FIXME
}

bool
sanguis::server::entities::exp_area::server_only() const
{
	return true;
}

void
sanguis::server::entities::exp_area::collision_begin(
	entities::with_body &_entity
)
{
	player_links_.insert(
		_entity.id(),
		_entity.link()
	);
}

void
sanguis::server::entities::exp_area::collision_end(
	entities::with_body &_entity
)
{
	player_links_.erase(
		_entity.id()
	);
}
