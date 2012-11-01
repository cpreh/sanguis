#ifndef SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_RESULT_HPP_INCLUDED

#include <sanguis/creator/generator/result_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace generator
{
namespace deserialization
{

sanguis::creator::generator::result const
result(
	sge::parse::json::object const &
);

}
}
}
}
}

#endif
