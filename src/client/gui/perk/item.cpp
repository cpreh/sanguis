#include "item.hpp"
#include "../object.hpp"
#include "../../perk/to_string.hpp"
#include <sge/cegui/to_cegui_string.hpp>
#include <CEGUI/elements/CEGUITree.h>

sanguis::client::gui::perk::item::item(
	CEGUI::Tree &_tree,
	client::gui::object &_gui,
	sanguis::perk_type::type const _type
)
:
	tree_(_tree),
	widget_(
		sge::cegui::to_cegui_string(
			client::perk::to_string(
				_type
			),
			_gui.charconv_system()
		),
		0, // item id
		0, // user data
		false, // enabled
		false // auto delete
	)
{
	tree_.addItem(
		&widget_
	);
}

sanguis::client::gui::perk::item::~item()
{
	tree_.removeItem(
		&widget_
	);
}
