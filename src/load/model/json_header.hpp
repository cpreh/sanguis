#ifndef SANGUIS_LOAD_MODEL_JSON_HEADER_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_JSON_HEADER_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/member_vector.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

sge::parse::json::object const &
json_header(
	sge::parse::json::member_vector const &
);

}
}
}

#endif
