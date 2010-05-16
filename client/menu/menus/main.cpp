#include "main.hpp"
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::client::menu::menus::main::main(
	sge::gui::widgets::parent_data const &_parent,
	sge::gui::dim const &_resolution,
	fcppt::filesystem::path const &buttons_path,
	sge::image::multi_loader const &image_loader_
)
:
	parent(
		_parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point::null()
			)
			.size(
				_resolution
			)
			.activation(
				sge::gui::activation_state::inactive
			)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::vertical>()
			)
	),
	connect(
		parent,
		image_loader_,
		buttons_path,
		FCPPT_TEXT("connect_menu")
	),
	start(
		parent,
		image_loader_,
		buttons_path,
		FCPPT_TEXT("quickstart")
	),
	highscore(
		parent,
		image_loader_,
		buttons_path,
		FCPPT_TEXT("highscores")
	),
	exit(
		parent,
		image_loader_,
		buttons_path,
		FCPPT_TEXT("quit")
	)
{
}
