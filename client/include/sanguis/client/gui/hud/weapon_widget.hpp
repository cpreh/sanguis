#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_WIDGET_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_WIDGET_HPP_INCLUDED

#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/image_fwd.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

class weapon_widget
{
	FCPPT_NONCOPYABLE(
		weapon_widget
	);
public:
	weapon_widget(
		sanguis::client::load::hud::context &,
		sanguis::gui::context &,
		sge::renderer::device::ffp &,
		sge::font::object &
	);

	~weapon_widget();

	void
	weapon_description(
		sanguis::optional_weapon_description const &
	);

	void
	magazine_remaining(
		sanguis::magazine_remaining
	);

	sanguis::gui::widget::box_container &
	widget();

	sanguis::optional_weapon_description const &
	weapon_description() const;
private:
	void
	update_text(
		sanguis::magazine_remaining
	);

	sanguis::client::load::hud::context &resources_;

	sge::renderer::device::ffp &renderer_;

	typedef
	std::unique_ptr<
		sanguis::gui::widget::image
	>
	image_unique_ptr;

	image_unique_ptr image_;

	sanguis::gui::widget::text text_;

	sanguis::gui::widget::box_container container_;

	sanguis::optional_weapon_description description_;
};

}
}
}
}

#endif
