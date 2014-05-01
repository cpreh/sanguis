#ifndef SANGUIS_CREATOR_AUX__DESERIALIZATION_DESTRUCTIBLE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__DESERIALIZATION_DESTRUCTIBLE_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/destructible_container.hpp>
#include <sge/parse/json/array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace deserialization
{

sanguis::creator::destructible_container
destructible_container(
	sge::parse::json::array const &
);

}
}
}
}

#endif
