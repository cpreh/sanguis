#include "highscore.hpp"
#include "../../highscore/read.hpp"
#include "../../config/homedir.hpp"
#include <sge/font/text/lit.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/widgets/parent_data.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <boost/foreach.hpp>

sanguis::client::menu::menus::highscore::highscore(
	sge::gui::widgets::parent_data const &_parent,
	fcppt::filesystem::path const &
)
:
	parent(
		_parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point::null()
			)
			.size(
				sge::gui::dim(1024,768)
			)
			.activation(
				sge::gui::activation_state::inactive
			)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	table(
		parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,0)
			)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	back_button(
		parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,1)
			),
		SGE_FONT_TEXT_LIT("Back")
	),
	children()
{
	populate_children();
}

void
sanguis::client::menu::menus::highscore::populate_children()
{
	fcppt::io::ifstream file(
		config::homedir()/
		FCPPT_TEXT("highscore")
	);

	sanguis::client::highscore::table const read_table(
		file.is_open()
		?
			sanguis::client::highscore::read(
				file
			)
		:
			sanguis::client::highscore::table()
	);

	fcppt::container::ptr::push_back_unique_ptr(
		children,
		fcppt::make_unique_ptr<
			sge::gui::widgets::label
		>(
			sge::gui::widgets::parent_data(
				table
			),
			sge::gui::widgets::parameters()
				.pos(
					sge::gui::point(0,0)
				),
			SGE_FONT_TEXT_LIT("Name(s)")
		)
	);

	fcppt::container::ptr::push_back_unique_ptr(
		children,
		fcppt::make_unique_ptr<
			sge::gui::widgets::label
		>(
			sge::gui::widgets::parent_data(
				table
			),
			sge::gui::widgets::parameters()
				.pos(
					sge::gui::point(1,0)
				),
			SGE_FONT_TEXT_LIT("Score")
		)
	);

	sge::gui::unit y_pos = 1;
	BOOST_FOREACH(
		sanguis::client::highscore::entry const &e,
		read_table
	)
	{
		fcppt::container::ptr::push_back_unique_ptr(
			children,
			fcppt::make_unique_ptr<
				sge::gui::widgets::label
			>(
				sge::gui::widgets::parent_data(
					table
				),
				sge::gui::widgets::parameters()
					.pos(
						sge::gui::point(0,y_pos)
					),
				sge::font::text::from_fcppt_string(
					fcppt::algorithm::join_strings(
						e.names(),
						FCPPT_TEXT(", ")
					)
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			children,
			fcppt::make_unique_ptr<
				sge::gui::widgets::label
			>(
				sge::gui::widgets::parent_data(
					table
				),
				sge::gui::widgets::parameters()
					.pos(
						sge::gui::point(1,y_pos)
					),
				fcppt::lexical_cast<
					sge::font::text::string
				>(
					e.score()
				)
			)
		);

		++y_pos;
	}
}
