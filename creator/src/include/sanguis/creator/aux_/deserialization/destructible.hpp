#ifndef SANGUIS_CREATOR_AUX__DESERIALIZATION_DESTRUCTIBLE_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__DESERIALIZATION_DESTRUCTIBLE_HPP_INCLUDED

#include <sanguis/creator/destructible_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace deserialization
{

sanguis::creator::destructible
destructible(
	sge::parse::json::object const &
);

}
}
}
}

#endif
