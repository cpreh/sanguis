#ifndef SANGUIS_LOAD_MODEL_PATH_TO_JSON_FILE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PATH_TO_JSON_FILE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

boost::filesystem::path
path_to_json_file(
	boost::filesystem::path
);

}
}
}

#endif
