#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_HPP_INCLUDED

#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
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
		sanguis::gui::context &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::weapon_description const &
	);

	~weapon_tooltip();

	sanguis::gui::widget::base &
	widget();
private:
	sanguis::gui::widget::text name_text_;

	typedef
	std::unique_ptr<
		sanguis::gui::widget::text
	>
	text_unique_ptr;

	typedef
	std::vector<
		text_unique_ptr
	>
	text_unique_ptr_vector;

	text_unique_ptr_vector attribute_texts_;

	sanguis::gui::widget::box_container container_;
};

}
}
}
}

#endif
