#ifndef SANGUIS_CLIENT_ARGS_ELEMENTS_LOG_LEVEL_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_ELEMENTS_LOG_LEVEL_FWD_HPP_INCLUDED

#include <sanguis/client/args/labels/log_level.hpp>
#include <fcppt/log/level_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::client::args::elements
{

using log_level =
    fcppt::record::element<sanguis::client::args::labels::log_level, fcppt::log::level>;

}

#endif
