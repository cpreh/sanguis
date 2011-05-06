#ifndef SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_RESULT_HPP_INCLUDED

#include <sanguis/creator/generator/result_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{
namespace deserialization
{

generator::result const
result(
	sge::parse::json::object const &
);

}
}
}
}

#endif
