#ifndef SANGUIS_LOAD_MODEL_PARSE_JSON_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PARSE_JSON_HPP_INCLUDED

#include <sge/parse/json/start_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

void
parse_json(
	boost::filesystem::path const &,
	sge::parse::json::start &
);

}
}
}

#endif
