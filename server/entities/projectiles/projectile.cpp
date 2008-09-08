#include "projectile.hpp"
#include "../base_parameters.hpp"
#include "../../collision.hpp"
#include "../../damage_types.hpp"
#include "../../message_converter.hpp"
#include <sge/time/second.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

namespace
{

sanguis::entity_type::type
to_entity_type(
	sanguis::projectile_type::type);

}

sanguis::projectile_type::type
sanguis::server::entities::projectiles::projectile::ptype() const
{
	return ptype_;
}

sanguis::server::entities::projectiles::projectile::projectile(
	projectile_type::type const nptype,
	environment const &env,
	pos_type const& center,
	space_unit const angle,
	team::type const team_,
	property_map const &properties,
	dim_type const &dim,
	time_type const lifetime)
:
	entity(
		base_parameters(
			env,
			damage::list(
				messages::mu(0)),
			center,
			angle,
			angle,
			team_,
			properties,
			to_entity_type(nptype),
			true,
			dim)),
	ptype_(nptype),
	lifetime(
		sge::time::second(
			lifetime))
{}

void sanguis::server::entities::projectiles::projectile::die()
{
	entity::die();
	do_die();
}

void sanguis::server::entities::projectiles::projectile::update(
	time_type const time,
	container &entities)
{
	entity::update(
		time,
		entities);

	if(lifetime.expired())
	{
		die();
		return;
	}

	hit_vector hits;

	BOOST_FOREACH(
		entity &e,
		entities)
	{
		if(e.team() != team()
		&& !e.dead()
		&& collides(
			e,
			*this))
			hits.push_back(
				hit_vector::value_type(e));
	}

	if(!hits.empty())
		do_hit(hits);
}

void sanguis::server::entities::projectiles::projectile::do_die()
{}

sanguis::messages::auto_ptr
sanguis::server::entities::projectiles::projectile::add_message() const
{
	return message_convert(*this);	
}

namespace
{

sanguis::entity_type::type
to_entity_type(
	sanguis::projectile_type::type const p)
{
	// TODO: maybe this is not the best way to do this
	switch(p) {
	case sanguis::projectile_type::rocket:
	case sanguis::projectile_type::simple_bullet:
		return sanguis::entity_type::projectile;
	case sanguis::projectile_type::aoe_damage:
	case sanguis::projectile_type::melee:
		return sanguis::entity_type::indeterminate;
	default:
		throw sge::exception(
			SGE_TEXT("Invalid projectile type in to_entity_type()!"));
	}
}

}


