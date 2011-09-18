#include <sanguis/client/gui/perk/item.hpp>
#include <sanguis/client/gui/perk/node.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <elements/CEGUITree.h>
#include <fcppt/config/external_end.hpp>

sanguis::client::gui::perk::item::item(
	client::gui::perk::node const &_parent,
	client::gui::object &_gui,
	client::perk::info const &_info
)
:
	parent_(_parent),
	perk_type_(
		_info.type()
	),
	widget_(
		sge::cegui::to_cegui_string(
			client::perk::to_string(
				perk_type_
			),
			_gui.charconv_system()
		),
		0, // item id
		const_cast<
			sanguis::perk_type::type *
		>(
			&perk_type_
		), // user data
		false, // disabled
		false // auto delete
	)
{
	parent_.add_item(
		widget_
	);

	if(
		!widget_.getIsOpen()
	)
		widget_.toggleIsOpen();
}

sanguis::client::gui::perk::item::~item()
{
	parent_.remove_item(
		widget_
	);
}

sanguis::perk_type::type
sanguis::client::gui::perk::item::perk_type() const
{
	return perk_type_;
}

CEGUI::TreeItem &
sanguis::client::gui::perk::item::widget()
{
	return widget_;
}
