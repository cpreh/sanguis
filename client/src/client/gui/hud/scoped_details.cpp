#include <sanguis/client/gui/hud/object.hpp>
#include <sanguis/client/gui/hud/scoped_details.hpp>


sanguis::client::gui::hud::scoped_details::scoped_details(
	sanguis::client::gui::hud::object &_hud
)
:
	hud_(
		_hud
	)
{
	hud_.details(
		true
	);
}

sanguis::client::gui::hud::scoped_details::~scoped_details()
{
	hud_.details(
		false
	);
}
