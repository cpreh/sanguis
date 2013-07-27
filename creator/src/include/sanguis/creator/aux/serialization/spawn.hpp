#ifndef SANGUIS_CREATOR_AUX_SERIALIZATION_SPAWN_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_SERIALIZATION_SPAWN_HPP_INCLUDED

#include <sanguis/creator/spawn_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace serialization
{

sge::parse::json::object
spawn(
	sanguis::creator::spawn const &
);

}
}
}
}

#endif
