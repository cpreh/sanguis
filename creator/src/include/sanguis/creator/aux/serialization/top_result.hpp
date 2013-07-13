#ifndef SANGUIS_CREATOR_AUX_SERIALIZATION_TOP_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_SERIALIZATION_TOP_RESULT_HPP_INCLUDED

#include <sanguis/creator/top_result_fwd.hpp>
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
top_result(
	sanguis::creator::top_result const &
);

}
}
}
}

#endif
