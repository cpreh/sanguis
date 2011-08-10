#include "exp_area.hpp"
#include "player.hpp"
#include "auto_weak_link.hpp"
#include "collision_groups.hpp"
#include "../collision/circle_ghost.hpp"
#include "../entities/base.hpp"
#include "../entities/player.hpp"
#include "../../messages/base.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/dynamic_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::entities::exp_area::exp_area(
	server::exp const _exp
)
:
	entities::with_ghosts(),
	exp_(_exp),
	player_links_()
{
	this->add_ghost(
		collision::ghost_unique_ptr(
			fcppt::make_unique_ptr<
				collision::circle_ghost
			>(
				entities::collision_groups(
					this->type(),
					this->team()
				),
				server::radius(
					2000 // TODO
				),
				this->body_enter_callback(),
				this->body_exit_callback()
			)
		)
	);
}

sanguis::server::entities::exp_area::~exp_area()
{
}

sanguis::server::center const
sanguis::server::entities::exp_area::center() const
{
	// FIXME: This is not needed anywhere!
	return
		server::center(
			server::center::value_type::null()
		);
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
		weak_link_map::iterator it(
			player_links_.begin()
		);
		it != player_links_.end();
		++it
	)
		fcppt::dynamic_cast_<
			player &
		>(
			*it->second
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

boost::logic::tribool const
sanguis::server::entities::exp_area::can_collide_with(
	collision::body_base const &_base
) const
{
	return
		dynamic_cast<
			entities::player const *
		>(
			&_base
		)
		!= 0;
}

void
sanguis::server::entities::exp_area::body_enter(
	collision::body_base &_body
)
{
	entities::base &entity(
		dynamic_cast<
			entities::base &
		>(
			_body
		)
	);

	player_links_.insert(
		entity.id(),
		entity.link()
	);
}

void
sanguis::server::entities::exp_area::body_exit(
	collision::body_base &_body
)
{
	player_links_.erase(
		dynamic_cast<
			entities::base const &
		>(
			_body
		).id()
	);
}
