#ifndef SANGUIS_CLIENT_GUI_MENU_RESOLUTION_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_RESOLUTION_CHOOSER_HPP_INCLUDED

#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/choices.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace menu
{

class resolution_chooser
{
	FCPPT_NONCOPYABLE(
		resolution_chooser
	);
public:
	resolution_chooser(
		sge::gui::context_ref,
		sge::gui::style::const_reference,
		sge::font::object_ref,
		sge::renderer::device::ffp_ref
	);

	~resolution_chooser();

	sge::gui::widget::base &
	widget();
private:
	void
	on_apply();

	sge::renderer::display_mode::container const display_modes_;

	sge::renderer::device::ffp_ref const renderer_;

		sge::gui::widget::choices choices_;

		sge::gui::widget::button apply_button_;

	sge::gui::widget::box_container widget_;

	fcppt::signal::auto_connection const apply_connection_;
};

}
}
}
}

#endif
