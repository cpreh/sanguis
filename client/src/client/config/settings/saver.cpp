#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/config/settings/saver.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/log/out.hpp>

sanguis::client::config::settings::saver::saver(
    fcppt::reference<sanguis::client::config::settings::object const> const _object)
    : object_(_object)
{
}

sanguis::client::config::settings::saver::~saver()
{
  try
  {
    object_->save();
  }
  catch (fcppt::exception const &_error)
  {
    FCPPT_LOG_FATAL(
        object_->log(),
        fcppt::log::out << FCPPT_TEXT("Saving your settings failed: ") << _error.string())
  }
}
