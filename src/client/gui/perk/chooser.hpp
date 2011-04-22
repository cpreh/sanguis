#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include "chooser_fwd.hpp"
#include "item_tree.hpp"
#include "../object_fwd.hpp"
#include "../../level.hpp"
#include "../../perk/state_fwd.hpp"
#include "../../perk/tree.hpp"
#include "../../../perk_type.hpp"
#include "../../../time_type.hpp"
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <fcppt/container/tree/object_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <CEGUI/CEGUIEvent.h>

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
		time_type
	);

	void
	draw();
private:
	void
	perks(
		client::perk::tree const &
	);

	void
	level(
		client::level
	);

	void
	update_top_widget();

	bool
	handle_selection_changed(
		CEGUI::EventArgs const &
	);

	gui::object &gui_;

	client::perk::state &state_;

	fcppt::signal::scoped_connection const
		perk_connection_,
		level_connection_;

	sge::cegui::toolbox::scoped_layout const scoped_layout_;

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet_;

	CEGUI::Tree &tree_widget_;

	CEGUI::Window &top_widget_;

	CEGUI::Event::ScopedConnection const
		selection_connection_;

	gui::perk::item_tree items_;
};

}
}
}
}

#endif
