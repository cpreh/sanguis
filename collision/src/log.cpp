#include <sanguis/collision/log.hpp>
#include <sanguis/collision/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters_no_function.hpp>

sanguis::collision::log::log(fcppt::log::context_reference const _log_context)
    : body_log_{
          _log_context,
          sanguis::collision::log_location(),
          fcppt::log::parameters_no_function(fcppt::log::name{FCPPT_TEXT("body")})}
{
}

sanguis::collision::log::~log() = default;

fcppt::log::object &sanguis::collision::log::body_log() const { return body_log_; }
