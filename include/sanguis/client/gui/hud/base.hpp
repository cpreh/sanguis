#ifndef SANGUIS_CLIENT_GUI_HUD_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_BASE_HPP_INCLUDED

#include <sanguis/client/gui/hud/area_callback.hpp>
#include <sanguis/client/gui/hud/base_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	sge::rucksack::rect const
	area() const = 0;

	virtual
	fcppt::signal::auto_connection
	area_change(
		sanguis::client::gui::hud::area_callback const &
	) = 0;
};

}
}
}
}

#endif
