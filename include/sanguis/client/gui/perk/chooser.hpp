#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include <sanguis/client/gui/perk/chooser_fwd.hpp>
#include <sanguis/client/gui/perk/item_tree.hpp>
#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/duration.hpp>
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/container/tree/object_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Event.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class Tree;
class Window;
}

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class chooser
{
	FCPPT_NONCOPYABLE(
		chooser
	);
public:
	chooser(
		gui::object &,
		client::perk::state &
	);

	~chooser();

	void
	process(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	void
	perks(
		client::perk::tree const &
	);

	void
	level(
		client::player_level
	);

	void
	update_top_text();

	void
	update_bottom_text(
		sanguis::perk_type::type
	);

	void
	update_tree_data();

	void
	update_choose_button(
		sanguis::perk_type::type
	);

	bool
	handle_selection_changed(
		CEGUI::EventArgs const &
	);

	bool
	handle_perk_choose(
		CEGUI::EventArgs const &
	);

	typedef fcppt::optional<
		perk_type::type
	> optional_perk;

	gui::object &gui_;

	client::perk::state &state_;

	optional_perk active_perk_;

	fcppt::signal::scoped_connection const
		perk_connection_,
		level_connection_;

	sge::cegui::toolbox::scoped_layout const scoped_layout_;

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet_;

	CEGUI::Tree &tree_widget_;

	CEGUI::Window
		&top_text_,
		&bottom_text_,
		&choose_button_;

	CEGUI::Event::ScopedConnection const
		selection_connection_,
		choose_connection_;

	gui::perk::item_tree items_;
};

}
}
}
}

#endif
