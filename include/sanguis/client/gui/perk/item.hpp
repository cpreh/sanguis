#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/gui/perk/item_fwd.hpp>
#include <sanguis/client/gui/perk/node.hpp>
#include <sanguis/client/perk/info_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/widgets/TreeItem.h>
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
		sanguis::client::gui::perk::node const &,
		sanguis::client::gui::object &,
		sanguis::client::perk::info const &
	);

	~item();

	sanguis::perk_type
	perk_type() const;

	CEGUI::TreeItem &
	widget();
private:
	sanguis::client::gui::perk::node const parent_;

	sanguis::perk_type const perk_type_;

	CEGUI::TreeItem widget_;
};

}
}
}
}

#endif
