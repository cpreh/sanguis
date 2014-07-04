#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_ATTRIBUTE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_ATTRIBUTE_HPP_INCLUDED

#include <sanguis/weapon_attribute_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/expander.hpp>
#include <sanguis/gui/widget/static_text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hover
{

class weapon_attribute
{
	FCPPT_NONCOPYABLE(
		weapon_attribute
	);
public:
	weapon_attribute(
		sanguis::gui::context &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::weapon_attribute const &
	);

	~weapon_attribute();

	sanguis::gui::widget::base &
	widget();
private:
	sanguis::gui::widget::static_text name_;

	sanguis::gui::widget::expander expander1_;

	sanguis::gui::widget::static_text value_;

	sanguis::gui::widget::static_text diff_;

	sanguis::gui::widget::box_container container_;
};

}
}
}
}
}

#endif
