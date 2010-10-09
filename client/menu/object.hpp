#ifndef SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED

#include "callbacks/object.hpp"
#include "menus/main.hpp"
#include "menus/connect.hpp"
#include "menus/connect_box.hpp"
#include "menus/highscore.hpp"
#include "button.hpp"
#include "mover.hpp"
#include "../config/settings/object_fwd.hpp"
#include "../cursor/object_ptr.hpp"
#include "../../time_type.hpp"
#include <sge/font/metrics_ptr.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/manager.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/parameters_fwd.hpp>

#include <fcppt/filesystem/path.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
class object
{
	FCPPT_NONCOPYABLE(object)
public:
	object(
		config::settings::object &,
		sge::renderer::device_ptr,
		sge::image::multi_loader &,
		sge::font::metrics_ptr,
		sge::input::processor_ptr,
		cursor::object_ptr,
		callbacks::object const &
	);

	~object();

	void
	process(
		time_type
	);

	void
	connection_error(
		fcppt::string const &message
	);
private:
	fcppt::filesystem::path const 
		menu_path,
		buttons_path,
		labels_path;

	sge::gui::manager m;

	menus::main main_;

	menus::connect connect_;

	menus::connect_box connect_box_;

	menus::highscore highscore_;
	
	mover mover_;

	fcppt::signal::connection_manager connections_;

	callbacks::object const callbacks_;

	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			sge::sprite::no_color
		>,
		boost::mpl::vector1<
			sge::sprite::with_texture
		>
	> sprite_choices;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system ss;
	sprite_object const background;

	fcppt::string 
		connection_host_,
		connection_port_;

	void
	start_server();

	void
	connect_from_menu();

	void
	connect(
		fcppt::string const &,
		fcppt::string const &
	);

	void
	cancel_connect();
};
}
}
}

#endif // SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
