#ifndef SANGUIS_CLIENT_ARGS_ELEMENTS_HISTORY_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_ELEMENTS_HISTORY_SIZE_FWD_HPP_INCLUDED

#include <sanguis/client/args/labels/history_size.hpp>
#include <sge/console/gfx/output_line_limit_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::client::args::elements
{

using history_size = fcppt::record::
    element<sanguis::client::args::labels::history_size, sge::console::gfx::output_line_limit>;

}

#endif
