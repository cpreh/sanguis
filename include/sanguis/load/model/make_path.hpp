#ifndef SANGUIS_LOAD_MODEL_MAKE_PATH_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_PATH_HPP_INCLUDED

#include <fcppt/string.hpp>
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
make_path(
	fcppt::string const &name
);

}
}
}

#endif
