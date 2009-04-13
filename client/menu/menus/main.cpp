#include "main.hpp"
#include "../../../resolution.hpp"
#include <sge/gui/layouts/vertical.hpp>
#include <sge/systems/instance.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/structure_cast.hpp>
#include <sge/text.hpp>

sanguis::client::menu::menus::main::main(
	sge::gui::widget::parent_data const &_parent,
	sge::filesystem::path const &buttons_path,
	sge::systems::instance &sys)
:
	parent(
		_parent,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point::null())
			.size(
				sge::structure_cast<sge::gui::dim>(
					resolution()))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),
	connect(
		parent,
		sys.image_loader(),
		buttons_path,
		SGE_TEXT("connect_menu")),
	start(
		parent,
		sys.image_loader(),
		buttons_path,
		SGE_TEXT("quickstart")),
	exit(
		parent,
		sys.image_loader(),
		buttons_path,
		SGE_TEXT("quit"))
{
}
