#include "exp_area.hpp"
#include "player.hpp"
#include "auto_weak_link.hpp"
#include "collision_groups.hpp"
#include "../collision/circle_ghost.hpp"
#include "../entities/base.hpp"
#include "../../messages/base.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/foreach.hpp>

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
				server::center(
					server::center::value_type::null()
				),
				server::radius(
					2000 // TODO
				),
				std::tr1::bind(
					&exp_area::collision_begin,
					this,
					std::tr1::placeholders::_1
				),
				std::tr1::bind(
					&exp_area::collision_end,
					this,
					std::tr1::placeholders::_1
				)
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
	collision::body_base &_entity
)
{
	// TODO: put this back in the base class?
	entities::base *const base(
		dynamic_cast<
			entities::base *
		>(
			&_entity
		)
	);

	if(
		!base
	)
		return;

	player_links_.insert(
		base->id(),
		base->link()
	);
}

void
sanguis::server::entities::exp_area::collision_end(
	collision::body_base &_entity
)
{
	// TODO: put this back in the base class?
	entities::base *const base(
		dynamic_cast<
			entities::base *
		>(
			&_entity
		)
	);

	if(
		!base
	)
		return;

	player_links_.erase(
		base->id()
	);
}
