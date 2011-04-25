#ifndef SANGUIS_CLIENT_GUI_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "../cursor/object_fwd.hpp"
#include "../../time_delta_fwd.hpp"
#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/default_keyboard.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/charconv/system_ptr.hpp>
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
		sge::renderer::device_ptr,
		sge::image2d::multi_loader &,
		sge::charconv::system_ptr,
		sge::viewport::manager &,
		sge::input::keyboard::device_ptr,
		client::cursor::object &
	);
	
	~object();

	sge::charconv::system_ptr const
	charconv_system() const;

	void
	render();

	void
	update(
		sanguis::time_delta const &
	);
private:
	sge::charconv::system_ptr const charconv_system_;

	sge::cegui::system system_;

	sge::cegui::syringe syringe_;

	sge::cegui::default_keyboard keyboard_;

	sge::cegui::default_cursor cursor_;
};

}
}
}

#endif
