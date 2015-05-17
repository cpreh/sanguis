#ifndef SANGUIS_TILES_PATH_REFERENCE_FWD_HPP_INCLUDED
#define SANGUIS_TILES_PATH_REFERENCE_FWD_HPP_INCLUDED

#include <fcppt/reference_wrapper_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

typedef
fcppt::reference_wrapper<
	boost::filesystem::path const
>
path_reference;

}
}

#endif
