#ifndef SANGUIS_CLIENT_GUI_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_OBJECT_HPP_INCLUDED

#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/cursor/object_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/default_keyboard.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::renderer::device::ffp &,
		sge::image2d::system &,
		sge::viewport::manager &,
		sge::input::keyboard::device &,
		client::cursor::object &
	);

	~object();

	sge::cegui::system &
	system();

	void
	render(
		sge::renderer::context::ffp &
	);

	void
	update(
		sanguis::duration const &
	);
private:
	sge::cegui::system system_;

	sge::cegui::syringe syringe_;

	sge::cegui::default_keyboard keyboard_;

	sge::cegui::default_cursor cursor_;
};

}
}
}

#endif
