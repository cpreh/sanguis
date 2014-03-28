#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_HPP_INCLUDED

#include <sanguis/model/object.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{

SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
sanguis::model::object
merge_paths(
	boost::filesystem::path const &
);

}
}
}

#endif
