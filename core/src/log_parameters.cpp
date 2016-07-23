#include <sanguis/log_parameters.hpp>
#include <sanguis/log_stream.hpp>
#include <fcppt/log/default_level_streams.hpp>
#include <fcppt/log/name_fwd.hpp>
#include <fcppt/log/parameters.hpp>
#include <fcppt/log/format/optional_function.hpp>


fcppt::log::parameters
sanguis::log_parameters(
	fcppt::log::name const &_name
)
{
	return
		fcppt::log::parameters{
			_name,
			fcppt::log::default_level_streams(
				sanguis::log_stream()
			),
			fcppt::log::format::optional_function()
		};
}
