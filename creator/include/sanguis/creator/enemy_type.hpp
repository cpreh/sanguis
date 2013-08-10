#ifndef SANGUIS_CREATOR_ENEMY_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_ENEMY_TYPE_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp>


namespace sanguis
{
namespace creator
{

enum class enemy_type
{
	wolf_black,
	wolf_brown,
	wolf_white,
	zombie00,
	zombie01,
	spider,
	skeleton,
	maggot,
	fcppt_maximum = maggot
};

}
}

#endif