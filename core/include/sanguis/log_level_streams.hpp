#ifndef SANGUIS_LOG_LEVEL_STREAMS_HPP_INCLUDED
#define SANGUIS_LOG_LEVEL_STREAMS_HPP_INCLUDED

#include <sanguis/core/symbol.hpp>
#include <fcppt/log/level_stream_array.hpp>

namespace sanguis
{

// TODO(philipp): Expose their real type here and use that in client::object
SANGUIS_CORE_SYMBOL
fcppt::log::level_stream_array log_level_streams();

}

#endif
