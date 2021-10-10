#ifndef SANGUIS_CLIENT_ARGS_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_RESULT_FWD_HPP_INCLUDED

#include <sanguis/client/args/elements/display_height.hpp>
#include <sanguis/client/args/elements/display_width.hpp>
#include <sanguis/client/args/elements/draw_debug.hpp>
#include <sanguis/client/args/elements/history_size.hpp>
#include <sanguis/client/args/elements/log_level.hpp>
#include <sanguis/client/args/elements/multi_samples.hpp>
#include <sanguis/client/args/elements/sge_log_level.hpp>
#include <sanguis/server/args/result.hpp>
#include <fcppt/record/disjoint_product.hpp>
#include <fcppt/record/object_impl.hpp>

namespace sanguis::client::args
{

using result = fcppt::record::disjoint_product<
    sanguis::server::args::result,
    fcppt::record::object<
        sanguis::client::args::elements::display_height,
        sanguis::client::args::elements::display_width,
        sanguis::client::args::elements::draw_debug,
        sanguis::client::args::elements::history_size,
        sanguis::client::args::elements::log_level,
        sanguis::client::args::elements::multi_samples,
        sanguis::client::args::elements::sge_log_level>>;

}

#endif
