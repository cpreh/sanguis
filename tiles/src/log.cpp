#include <sanguis/log_location.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/tiles/log.hpp>
#include <sanguis/tiles/impl/log_name.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/object.hpp>


sanguis::tiles::log::log(
	fcppt::log::context &_log_context
)
:
	main_log_{
		_log_context,
		sanguis::log_location(),
		sanguis::log_parameters(
			sanguis::tiles::impl::log_name()
		)
	}
{
}

sanguis::tiles::log::~log()
{
}

fcppt::log::object &
sanguis::tiles::log::main_log() const
{
	return
		main_log_;
}
