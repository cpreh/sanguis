#ifndef SANGUIS_LOAD_MODEL_PARSE_JSON_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PARSE_JSON_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

void
parse_json(
	fcppt::filesystem::path const &,
	sge::parse::json::object &
);

}
}
}

#endif
