#ifndef SANGUIS_CREATOR_AUX_DESERIALIZATION_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_DESERIALIZATION_RESULT_HPP_INCLUDED

#include <sanguis/creator/result_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace deserialization
{

sanguis::creator::result const
result(
	sge::parse::json::object const &
);

}
}
}
}

#endif
