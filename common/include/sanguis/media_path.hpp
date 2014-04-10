#ifndef SANGUIS_MEDIA_PATH_HPP_INCLUDED
#define SANGUIS_MEDIA_PATH_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

SANGUIS_COMMON_SYMBOL
boost::filesystem::path
media_path();

}

#endif
