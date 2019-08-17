#ifndef SANGUIS_LOAD_MODEL_MAKE_PATH_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_PATH_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/load/model/path_fwd.hpp>
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
make_path(
	sanguis::load::model::path const &
);

}
}
}

#endif
