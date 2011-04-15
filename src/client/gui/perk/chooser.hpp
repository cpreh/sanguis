#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include "chooser_fwd.hpp"
#include "item_fwd.hpp"
#include "../object_fwd.hpp"
#include "../../level.hpp"
#include "../../perk/container.hpp"
#include "../../perk/state_fwd.hpp"
#include "../../../perk_type.hpp"
#include "../../../time_type.hpp"
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace CEGUI
{
class Tree;
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
		client::perk::container const &
	);

	void
	level(
		client::level
	);

	gui::object &gui_;

	client::perk::state &state_;

	fcppt::signal::scoped_connection const
		perk_connection_,
		level_connection_;

	sge::cegui::toolbox::scoped_layout const scoped_layout_;

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet_;

	CEGUI::Tree &tree_widget_;

	typedef boost::ptr_vector<
		perk::item
	> item_vector;

	item_vector items_;
};

}
}
}
}

#endif
