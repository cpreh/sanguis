#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/weapon_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_unique_ptr.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/background/colored.hpp>
#include <sanguis/gui/main_area/fixed_position.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/image.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


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

class weapon
:
	public sanguis::client::draw2d::scene::hover::base
{
	FCPPT_NONCOPYABLE(
		weapon
	);
public:
	weapon(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::load::hud::context &,
		sanguis::client::draw2d::entities::hover::weapon const &
	);

	~weapon()
	override;
private:
	void
	draw(
		sge::renderer::context::ffp &
	)
	override;

	sanguis::gui::context gui_context_;

	sanguis::gui::widget::image image_;

	typedef
	std::vector<
		sanguis::client::draw2d::scene::hover::weapon_attribute_unique_ptr
	>
	weapon_attribute_vector;

	weapon_attribute_vector weapon_attributes_;

	sanguis::gui::widget::box_container container_;

	sanguis::gui::main_area::fixed_position gui_area_;

	sanguis::gui::background::colored gui_background_;
};

}
}
}
}
}

#endif
