#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_ATTRIBUTE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_ATTRIBUTE_HPP_INCLUDED

#include <sanguis/weapon_attribute_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_diff_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/expander.hpp>
#include <sge/gui/widget/static_text.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::scene::hover
{

class weapon_attribute
{
	FCPPT_NONMOVABLE(
		weapon_attribute
	);
public:
	weapon_attribute(
		sge::gui::context_ref,
		sge::gui::style::const_reference,
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sanguis::weapon_attribute const &,
		sanguis::client::draw2d::scene::hover::weapon_attribute_diff
	);

	~weapon_attribute();

	[[nodiscard]]
	sge::gui::widget::base &
	widget();
private:
	sge::gui::widget::static_text name_;

	sge::gui::widget::expander expander1_;

	sge::gui::widget::static_text value_;

	sge::gui::widget::expander expander2_;

	sge::gui::widget::static_text diff_;

	sge::gui::widget::box_container container_;
};

}

#endif
