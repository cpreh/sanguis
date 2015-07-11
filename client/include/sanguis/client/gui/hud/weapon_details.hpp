#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_DETAILS_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_DETAILS_HPP_INCLUDED

#include <sanguis/optional_weapon_description_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_details_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_unique_ptr.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

class weapon_details
{
	FCPPT_NONCOPYABLE(
		weapon_details
	);
public:
	weapon_details(
		sge::gui::context &,
		sanguis::client::load::hud::context &,
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::optional_weapon_description const &,
		sanguis::optional_weapon_description const &
	);

	~weapon_details();

	sge::gui::widget::base &
	widget();
private:
	typedef
	std::vector<
		sanguis::client::gui::hud::weapon_tooltip_unique_ptr
	>
	tooltip_vector;

	tooltip_vector tooltips_;

	sge::gui::widget::box_container container_;
};

}
}
}
}

#endif
