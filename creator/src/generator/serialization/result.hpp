#ifndef SANGUIS_CREATOR_GENERATOR_SERIALIZATION_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_SERIALIZATION_RESULT_HPP_INCLUDED

#include <sanguis/creator/generator/result_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{
namespace serialization
{

sge::parse::json::object const
result(
	generator::result const &
);

}
}
}
}

#endif
