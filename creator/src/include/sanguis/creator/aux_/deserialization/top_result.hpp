#ifndef SANGUIS_CREATOR_AUX__DESERIALIZATION_TOP_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__DESERIALIZATION_TOP_RESULT_HPP_INCLUDED

#include <sanguis/creator/top_result_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace deserialization
{

sanguis::creator::top_result
top_result(
	sge::parse::json::object const &
);

}
}
}
}

#endif
