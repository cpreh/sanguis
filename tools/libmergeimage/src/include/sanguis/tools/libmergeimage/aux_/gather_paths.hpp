#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__GATHER_PATHS_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__GATHER_PATHS_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/aux_/path_vector_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

sanguis::tools::libmergeimage::aux_::path_vector_vector
gather_paths(
	boost::filesystem::path const &
);

}
}
}
}

#endif
