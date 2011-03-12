#include "saver.hpp"
#include "object.hpp"
#include "../../log.hpp"
#include <fcppt/log/output.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>

sanguis::client::config::settings::saver::saver(
	object const &_object
)
:
	object_(_object)
{}

sanguis::client::config::settings::saver::~saver()
{
	try
	{
		object_.save();	
	}
	catch(
		fcppt::exception const &e
	)
	{
		FCPPT_LOG_FATAL(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Saving your settings failed: ")
				<< e.string()
		);
	}
}
