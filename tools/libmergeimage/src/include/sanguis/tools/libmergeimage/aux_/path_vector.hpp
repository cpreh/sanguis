#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__PATH_VECTOR_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__PATH_VECTOR_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

typedef
std::vector<
	boost::filesystem::path
>
path_vector;

}
}
}
}

#endif
