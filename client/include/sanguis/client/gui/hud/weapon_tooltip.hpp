#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_HPP_INCLUDED

#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_fwd.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/static_text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
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

class weapon_tooltip
{
	FCPPT_NONCOPYABLE(
		weapon_tooltip
	);
public:
	weapon_tooltip(
		sge::gui::context &,
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::weapon_description const &
	);

	~weapon_tooltip();

	sge::gui::widget::base &
	widget();
private:
	sge::gui::widget::static_text name_text_;

	typedef
	fcppt::unique_ptr<
		sge::gui::widget::static_text
	>
	text_unique_ptr;

	typedef
	std::vector<
		text_unique_ptr
	>
	text_unique_ptr_vector;

	text_unique_ptr_vector attribute_texts_;

	sge::gui::widget::box_container container_;
};

}
}
}
}

#endif
