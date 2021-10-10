#include <sanguis/log_location.hpp>
#include <sanguis/tiles/log.hpp>
#include <sanguis/tiles/impl/log_name.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters_no_function.hpp>

sanguis::tiles::log::log(fcppt::log::context_reference const _log_context)
    : main_log_{
          _log_context,
          sanguis::log_location(),
          fcppt::log::parameters_no_function(sanguis::tiles::impl::log_name())}
{
}

sanguis::tiles::log::~log() = default;

fcppt::log::object &sanguis::tiles::log::main_log() const { return main_log_; }
