#ifndef SANGUIS_SERVER_WAVES_CONVERT_ENEMY_NAME_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_CONVERT_ENEMY_NAME_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace server
{
namespace waves
{

sanguis::creator::enemy_type
convert_enemy_name(
	fcppt::string const &
);

}
}
}

#endif
