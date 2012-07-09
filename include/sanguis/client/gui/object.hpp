#ifndef SANGUIS_CLIENT_GUI_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_OBJECT_HPP_INCLUDED

#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/cursor/object_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/default_keyboard.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
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
		sge::renderer::device &,
		sge::image2d::system &,
		sge::charconv::system &,
		sge::viewport::manager &,
		sge::input::keyboard::device &,
		client::cursor::object &
	);

	~object();

	sge::charconv::system &
	charconv_system() const;

	sge::cegui::system &
	system();

	void
	render(
		sge::renderer::context::object &
	);

	void
	update(
		sanguis::duration const &
	);
private:
	sge::charconv::system &charconv_system_;

	sge::cegui::system system_;

	sge::cegui::syringe syringe_;

	sge::cegui::default_keyboard keyboard_;

	sge::cegui::default_cursor cursor_;
};

}
}
}

#endif
