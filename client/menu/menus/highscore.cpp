#include "highscore.hpp"
#include "../../highscore/read.hpp"
#include "../../config/homedir.hpp"
#include <sge/algorithm/join_strings.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/text.hpp>
#include <sge/fstream.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/foreach.hpp>

sanguis::client::menu::menus::highscore::highscore(
	sge::gui::widgets::parent_data const &_parent,
	sge::filesystem::path const &,
	sge::systems::instance const &)
:
	parent(
		_parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point::null())
			.size(
				sge::gui::dim(1023,768))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::grid>())),
	table(
		parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,0))
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::grid>())),
	back_button(
		parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,1)),
		SGE_TEXT("Back")),
	children()
{
	populate_children();
}

void sanguis::client::menu::menus::highscore::populate_children()
{
	sge::ifstream file(
		config::homedir()/
		SGE_TEXT("highscore"));
	sanguis::client::highscore::table const t = 
		sanguis::client::highscore::read(
			file);

	children.push_back(
		new sge::gui::widgets::label(
			table,
			sge::gui::widgets::parameters()
				.pos(
					sge::gui::point(0,0)),
			SGE_TEXT("Name(s)")));
	children.push_back(
		new sge::gui::widgets::label(
			table,
			sge::gui::widgets::parameters()
				.pos(
					sge::gui::point(1,0)),
			SGE_TEXT("Score")));

	sge::gui::unit y_pos = 1;
	BOOST_FOREACH(sanguis::client::highscore::entry const &e,t)
	{
		children.push_back(
			new sge::gui::widgets::label(
				table,
				sge::gui::widgets::parameters()
					.pos(
						sge::gui::point(0,y_pos)),
				sge::algorithm::join_strings(
					e.names(),
					SGE_TEXT(", "))));
		children.push_back(
			new sge::gui::widgets::label(
				table,
				sge::gui::widgets::parameters()
					.pos(
						sge::gui::point(1,y_pos)),
				sge::lexical_cast<sge::string>(e.score())));

		++y_pos;
	}
}
