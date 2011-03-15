#include "screenshot.hpp"
#include "config/homedir.hpp"
#include "make_screenshot_path.hpp"
#include "log.hpp"
#include "../exception.hpp"
#include <sge/renderer/screenshot.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/create_directory.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

sanguis::client::screenshot::screenshot(
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader const &_loader,
	sge::input::keyboard::device_ptr const _keyboard
)
:
	make_screenshot(
		std::tr1::bind(
			&sge::renderer::screenshot,
			_renderer,
			std::tr1::ref(
				_loader
			),
			std::tr1::placeholders::_1
		)
	),
	active_(false),
	ic(
		_keyboard->key_callback(
			std::tr1::bind(
				&screenshot::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

sanguis::client::screenshot::~screenshot()
{
}

void
sanguis::client::screenshot::process()
{
	if (!active_)
		return;

	fcppt::filesystem::path const 
		screenshot_path = make_screenshot_path(),
		dir = config::homedir()/FCPPT_TEXT("screenshots"),
		whole_path = dir / screenshot_path;
	
	if (!fcppt::filesystem::exists(dir))
		fcppt::filesystem::create_directory(dir);
	
	if (!fcppt::filesystem::is_directory(dir))
		throw exception(
			FCPPT_TEXT("Screenshot path ")
			+ fcppt::filesystem::path_to_string(
				whole_path
			)
			+ FCPPT_TEXT(" exists but is not a directory")
		);

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("writing screenshot: ")
			<< fcppt::filesystem::path_to_string(
				whole_path
			)
	);
	
	make_screenshot(
		whole_path
	);
		
	active_ = false;
}

void
sanguis::client::screenshot::input_callback(
	sge::input::keyboard::key_event const &_event
)
{
	if (!_event.pressed())
		return;

	if (_event.key_code() != sge::input::keyboard::key_code::print)
		return;
	
	active_ = true;
}
