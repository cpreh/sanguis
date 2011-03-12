#ifndef SANGUIS_CLIENT_SCREENSHOT_HPP_INCLUDED
#define SANGUIS_CLIENT_SCREENSHOT_HPP_INCLUDED

#include <sge/renderer/device_ptr.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{

class screenshot
{
	FCPPT_NONCOPYABLE(
		screenshot
	);
public:
	screenshot(
		sge::renderer::device_ptr,
		sge::image2d::multi_loader const &,
		sge::input::keyboard::device_ptr
	);

	~screenshot();

	void
	process();
private:
	fcppt::function::object<
		void (fcppt::filesystem::path const &)
	> make_screenshot;

	bool active_;
	fcppt::signal::scoped_connection const ic;

	void
	input_callback(
		sge::input::keyboard::key_event const &
	);
};

}
}

#endif // SANGUIS_CLIENT_SCREENSHOT_HPP_INCLUDED
