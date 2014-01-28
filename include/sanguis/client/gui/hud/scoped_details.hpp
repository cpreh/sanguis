#ifndef SANGUIS_CLIENT_GUI_HUD_SCOPED_DETAILS_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_SCOPED_DETAILS_HPP_INCLUDED

#include <sanguis/client/gui/hud/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

class scoped_details
{
	FCPPT_NONCOPYABLE(
		scoped_details
	);
public:
	explicit
	scoped_details(
		sanguis::client::gui::hud::object &
	);

	~scoped_details();
private:
	sanguis::client::gui::hud::object &hud_;
};

}
}
}
}

#endif
