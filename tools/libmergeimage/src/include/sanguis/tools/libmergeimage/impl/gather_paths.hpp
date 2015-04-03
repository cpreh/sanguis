#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_GATHER_PATHS_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_GATHER_PATHS_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace impl
{

sanguis::tools::libmergeimage::impl::path_vector_vector
gather_paths(
	boost::filesystem::path const &
);

}
}
}
}

#endif
