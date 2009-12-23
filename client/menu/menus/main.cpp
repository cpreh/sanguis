#include "main.hpp"
#include "../../../resolution.hpp"
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/systems/instance.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::client::menu::menus::main::main(
	sge::gui::widgets::parent_data const &_parent,
	fcppt::filesystem::path const &buttons_path,
	sge::systems::instance const &sys)
:
	parent(
		_parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point::null())
			.size(
				sge::math::dim::structure_cast<sge::gui::dim>(
					resolution()))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),
	connect(
		parent,
		sys.image_loader(),
		buttons_path,
		FCPPT_TEXT("connect_menu")),
	start(
		parent,
		sys.image_loader(),
		buttons_path,
		FCPPT_TEXT("quickstart")),
	highscore(
		parent,
		sys.image_loader(),
		buttons_path,
		FCPPT_TEXT("highscores")),
	exit(
		parent,
		sys.image_loader(),
		buttons_path,
		FCPPT_TEXT("quit"))
{
}
