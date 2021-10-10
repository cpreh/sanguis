#ifndef SANGUIS_SERVER_ARGS_ELEMENTS_LOG_LEVEL_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ARGS_ELEMENTS_LOG_LEVEL_FWD_HPP_INCLUDED

#include <sanguis/server/args/labels/log_level.hpp>
#include <fcppt/log/level_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::server::args::elements
{

using log_level =
    fcppt::record::element<sanguis::server::args::labels::log_level, fcppt::log::level>;

}

#endif
