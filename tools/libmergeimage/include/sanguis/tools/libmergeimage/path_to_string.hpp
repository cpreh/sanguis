#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_PATH_TO_STRING_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_PATH_TO_STRING_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{

SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
fcppt::string
path_to_string(
	sanguis::tools::libmergeimage::path const &
);

}
}
}

#endif
