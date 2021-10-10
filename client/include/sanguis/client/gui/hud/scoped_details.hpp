#ifndef SANGUIS_CLIENT_GUI_HUD_SCOPED_DETAILS_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_SCOPED_DETAILS_HPP_INCLUDED

#include <sanguis/client/gui/hud/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::client::gui::hud
{

class scoped_details
{
  FCPPT_NONMOVABLE(scoped_details);

public:
  using object_ref = fcppt::reference<sanguis::client::gui::hud::object>;

  explicit scoped_details(object_ref);

  ~scoped_details();

private:
  object_ref hud_;
};

}

#endif
