#ifndef SANGUIS_CLIENT_SCREENSHOT_HPP_INCLUDED
#define SANGUIS_CLIENT_SCREENSHOT_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/function/object.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace client
{
class screenshot
{
	SGE_NONCOPYABLE(screenshot)
public:
	screenshot(
		sge::renderer::device_ptr,
		sge::image::loader_ptr,
		sge::input::system_ptr);
	void process();
private:
	sge::function::object<
		void (sge::filesystem::path const &)
	> make_screenshot;

	bool active_;
	sge::signal::scoped_connection const ic;

	void input_callback(
		sge::input::key_pair const &);
};
}
}

#endif // SANGUIS_CLIENT_SCREENSHOT_HPP_INCLUDED
