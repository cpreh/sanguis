#ifndef SANGUIS_LOAD_MODEL_PATH_TO_JSON_FILE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PATH_TO_JSON_FILE_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

SANGUIS_COMMON_SYMBOL
std::filesystem::path
path_to_json_file(
	std::filesystem::path const &
);

}
}
}

#endif
