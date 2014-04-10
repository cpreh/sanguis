#ifndef SANGUIS_PROJECTILE_TYPE_HPP_INCLUDED
#define SANGUIS_PROJECTILE_TYPE_HPP_INCLUDED

#include <sanguis/projectile_type_fwd.hpp>


namespace sanguis
{

enum class projectile_type
{
	simple_bullet,
	aoe,
	fcppt_maximum = aoe
};

}

#endif
