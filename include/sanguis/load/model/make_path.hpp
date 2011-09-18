#ifndef SANGUIS_LOAD_MODEL_MAKE_PATH_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_PATH_HPP_INCLUDED

#include <fcppt/filesystem/path.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

fcppt::filesystem::path const
make_path(
	fcppt::string const &name
);

}
}
}

#endif
