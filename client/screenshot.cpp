#include "screenshot.hpp"
#include "config/homedir.hpp"
#include "make_screenshot_path.hpp"
#include "log.hpp"
#include "../exception.hpp"
#include <sge/renderer/screenshot.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/system.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/create_directory.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

sanguis::client::screenshot::screenshot(
	sge::renderer::device_ptr const _renderer,
	sge::image::loader_ptr const _loader,
	sge::input::system_ptr const is)
:
	make_screenshot(
		std::tr1::bind(
			&sge::renderer::screenshot,
			_renderer,
			_loader,
			std::tr1::placeholders::_1
		)
	),
	active_(false),
	ic(
		is->register_callback(
			std::tr1::bind(
				&screenshot::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

void sanguis::client::screenshot::process()
{
	if (!active_)
		return;

	fcppt::filesystem::path const 
		p = make_screenshot_path(),
		dir = config::homedir()/FCPPT_TEXT("screenshots");
	
	if (!fcppt::filesystem::exists(dir))
		fcppt::filesystem::create_directory(dir);
	
	if (!fcppt::filesystem::is_directory(dir))
		throw exception(
			FCPPT_TEXT("Screenshot path ")
			+ (dir / p).string()
			+ FCPPT_TEXT(" exists but is not a directory")
		);

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("writing screenshot: ")
			<< (dir/p)
	);
	
	make_screenshot(dir/p);
		
	active_ = false;
}

void sanguis::client::screenshot::input_callback(
	sge::input::key_pair const &k)
{
	if (k.value() == 0)
		return;

	if (k.key().code() != sge::input::kc::key_print)
		return;
	
	active_ = true;
}
