#include <sanguis/client/gui/hud/object.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/gui/hud/scoped_details.hpp>

sanguis::client::gui::hud::scoped_details::scoped_details(object_ref const _hud) : hud_(_hud)
{
  hud_->details(true);
}

sanguis::client::gui::hud::scoped_details::~scoped_details() { hud_->details(false); }
