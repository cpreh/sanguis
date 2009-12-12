#ifndef SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED

#include "callbacks/object.hpp"
#include "menus/main.hpp"
#include "menus/connect.hpp"
#include "menus/connect_box.hpp"
#include "menus/highscore.hpp"
#include "button.hpp"
#include "mover.hpp"
#include "../cursor/object_ptr.hpp"
#include "../../time_type.hpp"
#include <sge/systems/instance_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/manager.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/parameters_fwd.hpp>
#include <sge/signal/connection_manager.hpp>
#include <sge/noncopyable.hpp>
#include <sge/string.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
class object
{
	SGE_NONCOPYABLE(object)
public:
	object(
		sge::systems::instance const &,
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
		sge::string const &message
	);
private:
	sge::systems::instance const &sys_;
	
	sge::filesystem::path const 
		menu_path,
		buttons_path,
		labels_path;

	sge::gui::manager m;

	menus::main main_;
	menus::connect connect_;
	menus::connect_box connect_box_;
	menus::highscore highscore_;
	
	mover mover_;
	sge::signal::connection_manager connections_;
	callbacks::object const callbacks_;

	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			sge::sprite::no_clor
		>,
		boost::mpl::vector1<
			sge::sprite::with_texture
		>
	> sprite_choices;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::system<
		sprite_choies
	>::type sprite_system;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system ss;
	sprite_object const background;

	sge::string 
		connection_host_,
		connection_port_;

	void start_server();
	void connect_from_menu();
	void connect(
		sge::string const &,
		sge::string const &);
	void cancel_connect();
};
}
}
}

#endif // SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
