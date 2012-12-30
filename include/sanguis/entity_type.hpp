#ifndef SANGUIS_ENTITY_TYPE_HPP_INCLUDED
#define SANGUIS_ENTITY_TYPE_HPP_INCLUDED

#include <sanguis/entity_type_fwd.hpp>


namespace sanguis
{

enum class entity_type
{
	enemy,
	friend_,
	pickup,
	player,
	projectile,
	sentry,
	spawn
};

}

#endif
