#ifndef SANGUIS_TILES_PATH_REFERENCE_FWD_HPP_INCLUDED
#define SANGUIS_TILES_PATH_REFERENCE_FWD_HPP_INCLUDED

#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tiles
{

using path_reference = fcppt::reference<std::filesystem::path const>;

}

#endif
