#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_HPP_INCLUDED

#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/static_text.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::gui::hud
{

class weapon_tooltip
{
	FCPPT_NONMOVABLE(
		weapon_tooltip
	);
public:
	weapon_tooltip(
		sge::gui::context_ref,
		sge::gui::style::const_reference,
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sanguis::weapon_description const &
	);

	~weapon_tooltip();

	[[nodiscard]]
	sge::gui::widget::base &
	widget();
private:
	sge::gui::widget::static_text name_text_;

	using
	text_unique_ptr
	=
	fcppt::unique_ptr<
		sge::gui::widget::static_text
	>;

	using
	text_unique_ptr_vector
	=
	std::vector<
		text_unique_ptr
	>;

	text_unique_ptr_vector attribute_texts_;

	sge::gui::widget::box_container container_;
};

}

#endif
