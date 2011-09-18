#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED

#include <sanguis/client/gui/perk/item_fwd.hpp>
#include <sanguis/client/gui/perk/node.hpp>
#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/perk/info_fwd.hpp>
#include <sanguis/perk_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <elements/CEGUITreeItem.h>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class item
{
	FCPPT_NONCOPYABLE(
		item
	);
public:
	item(
		gui::perk::node const &,
		client::gui::object &,
		client::perk::info const &
	);

	~item();

	sanguis::perk_type::type
	perk_type() const;

	CEGUI::TreeItem &
	widget();
private:
	perk::node const parent_;

	sanguis::perk_type::type const perk_type_;

	CEGUI::TreeItem widget_;
};

}
}
}
}

#endif
