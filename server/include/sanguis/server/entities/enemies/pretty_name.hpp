#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_PRETTY_NAME_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_PRETTY_NAME_HPP_INCLUDED

#include <sanguis/creator/enemy_type.hpp>
#include <fcppt/string.hpp>


namespace sanguis::server::entities::enemies
{

fcppt::string
pretty_name(
	sanguis::creator::enemy_type
);

}

#endif

