#ifndef SANGUIS_CREATOR_AUX_DESERIALIZATION_SPAWN_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_DESERIALIZATION_SPAWN_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/spawn_container.hpp>
#include <sge/parse/json/array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace deserialization
{

sanguis::creator::spawn_container
spawn_container(
	sge::parse::json::array const &
);

}
}
}
}

#endif
