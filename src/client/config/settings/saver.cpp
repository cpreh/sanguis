#include <sanguis/client/log.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/config/settings/saver.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/log/output.hpp>


sanguis::client::config::settings::saver::saver(
	sanguis::client::config::settings::object const &_object
)
:
	object_(
		_object
	)
{
}

sanguis::client::config::settings::saver::~saver()
{
	try
	{
		object_.save();
	}
	catch(
		fcppt::exception const &_error
	)
	{
		FCPPT_LOG_FATAL(
			client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Saving your settings failed: ")
				<< _error.string()
		);
	}
}
