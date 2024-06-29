#include <sanguis/server/log_location.hpp>
#include <sanguis/server/weapons/log.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>

sanguis::server::weapons::log::log(fcppt::log::context_reference const _log_context)
    : main_log_{
          _log_context, sanguis::server::log_location(), fcppt::log::name{FCPPT_TEXT("weapons")}}
{
}

sanguis::server::weapons::log::~log() = default;

fcppt::log::object &sanguis::server::weapons::log::main_log() const { return main_log_; }
