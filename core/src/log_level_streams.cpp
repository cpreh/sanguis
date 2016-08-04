#include <sanguis/log_level_streams.hpp>
#include <fcppt/log/default_level_streams.hpp>
#include <fcppt/log/level_stream_array.hpp>


fcppt::log::level_stream_array
sanguis::log_level_streams()
{
	return
		fcppt::log::default_level_streams();
}
