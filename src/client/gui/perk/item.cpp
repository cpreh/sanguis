#include "item.hpp"
#include "../object.hpp"
#include "../../perk/to_string.hpp"
#include <sge/cegui/to_cegui_string.hpp>
#include <CEGUI/elements/CEGUITree.h>

sanguis::client::gui::perk::item::item(
	CEGUI::Tree &_tree,
	client::gui::object &_gui,
	sanguis::perk_type::type const _perk_type
)
:
	tree_(_tree),
	perk_type_(_perk_type),
	widget_(
		sge::cegui::to_cegui_string(
			client::perk::to_string(
				_perk_type
			),
			_gui.charconv_system()
		),
		0, // item id
		const_cast<
			sanguis::perk_type::type *
		>(
			&perk_type_
		), // user data
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
