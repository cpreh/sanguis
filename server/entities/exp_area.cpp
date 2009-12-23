#include "exp_area.hpp"
#include "player.hpp"
#include "auto_weak_link.hpp"
#include <fcppt/container/map_impl.hpp>
#include <sge/time/millisecond.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::exp_area::exp_area(
	exp_type const exp_
)
:
	exp_(exp_),
	diff_clock_(),
	expire_timer_(
		sge::time::millisecond(
			10
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	player_links_()
{}

sanguis::server::entities::exp_area::~exp_area()
{}

void
sanguis::server::entities::exp_area::on_update(
	time_type const time_
)
{
	diff_clock_.update(
		time_
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
			server::exp_type(
				exp_
				/ static_cast<exp_type::value_type>(
					player_links_.size()
				)
			)
		);	
}

sanguis::server::space_unit
sanguis::server::entities::exp_area::radius() const
{
	return static_cast<space_unit>(2000); // TODO!
}

bool
sanguis::server::entities::exp_area::dead() const
{
	return expire_timer_.expired();	
}

bool
sanguis::server::entities::exp_area::invulnerable() const
{
	return false;
}

sanguis::messages::auto_ptr
sanguis::server::entities::exp_area::add_message() const
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
sanguis::server::entities::exp_area::can_collide_with_entity(
	base const &entity_
) const
{
	return dynamic_cast<
		player const *
	>(
		&entity_
	);
}
	
void
sanguis::server::entities::exp_area::collision_entity_begin(
	base &entity_
)
{
	player_links_.insert(
		entity_.id(),
		entity_.link()
	);
}

void
sanguis::server::entities::exp_area::collision_entity_end(
	base &entity_
)
{
	player_links_.erase(
		entity_.id()
	);
}
