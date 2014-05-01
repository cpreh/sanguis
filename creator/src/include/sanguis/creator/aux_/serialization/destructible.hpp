#ifndef SANGUIS_CREATOR_AUX__SERIALIZATION_DESTRUCTIBLE_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__SERIALIZATION_DESTRUCTIBLE_HPP_INCLUDED

#include <sanguis/creator/destructible_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace serialization
{

sge::parse::json::object
destructible(
	sanguis::creator::destructible const &
);

}
}
}
}

#endif
