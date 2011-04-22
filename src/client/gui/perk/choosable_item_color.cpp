#include "choosable_item_color.hpp"
#include "../../../exception.hpp"
#include <sge/image/colors.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/text.hpp>

sge::image::color::any::object const
sanguis::client::gui::perk::choosable_item_color(
	client::perk::choosable_state::type const _state
)
{
	switch(
		_state
	)
	{
	case client::perk::choosable_state::ok:
		return sge::image::colors::white();
	case client::perk::choosable_state::parent_level:
	case client::perk::choosable_state::player_level:
		return sge::image::colors::red();
	case client::perk::choosable_state::max_level:
		return sge::image::colors::blue();
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid perk::choosable_state!")
	);
}
