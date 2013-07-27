#ifndef SANGUIS_CREATOR_AUX_SERIALIZATION_SPAWN_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_SERIALIZATION_SPAWN_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/spawn_container.hpp>
#include <sge/parse/json/array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace serialization
{

sge::parse::json::array
spawn_container(
	sanguis::creator::spawn_container const &
);

}
}
}
}

#endif
