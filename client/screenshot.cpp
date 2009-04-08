#include "screenshot.hpp"
#include "make_screenshot_path.hpp"
#include "log.hpp"
#include <sge/renderer/screenshot.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/math/compare.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/system.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>

sanguis::client::screenshot::screenshot(
	sge::renderer::device_ptr const _renderer,
	sge::image::loader_ptr const _loader,
	sge::input::system_ptr const is)
	: renderer_(_renderer),
		loader_(_loader),
	  active_(false),
		ic(
			is->register_callback(
				boost::bind(
					&screenshot::input_callback,
					this,
					_1)))
{
}

void sanguis::client::screenshot::process()
{
	if (!active_)
		return;
	
	sge::filesystem::path const p = 
		make_screenshot_path();
	
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("writing screenshot: ")
								 << p);
	
	sge::renderer::screenshot(
		renderer_,
		loader_,
		p);
		
	active_ = false;
}

void sanguis::client::screenshot::input_callback(
	sge::input::key_pair const &k)
{
	if (sge::math::almost_zero(k.value()))
		return;

	if (k.key().code() != sge::input::kc::key_print)
		return;
	
	active_ = true;
}
