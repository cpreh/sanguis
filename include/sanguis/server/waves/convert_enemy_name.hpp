#ifndef SANGUIS_SERVER_WAVES_CONVERT_ENEMY_NAME_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_CONVERT_ENEMY_NAME_HPP_INCLUDED

#include <sanguis/enemy_type.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

enemy_type::type
convert_enemy_name(
	fcppt::string const &
);

}
}
}

#endif
