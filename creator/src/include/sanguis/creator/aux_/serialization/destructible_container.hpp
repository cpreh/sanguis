#ifndef SANGUIS_CREATOR_AUX__SERIALIZATION_DESTRUCTIBLE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__SERIALIZATION_DESTRUCTIBLE_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/destructible_container.hpp>
#include <sge/parse/json/array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace serialization
{

sge::parse::json::array
destructible_container(
	sanguis::creator::destructible_container const &
);

}
}
}
}

#endif
