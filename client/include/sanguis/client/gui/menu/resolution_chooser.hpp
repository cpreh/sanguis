#ifndef SANGUIS_CLIENT_GUI_MENU_RESOLUTION_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_RESOLUTION_CHOOSER_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/choices.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/device/index_fwd.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


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
		sge::gui::context &,
		sge::gui::style::base const &,
		sge::font::object &,
		sge::renderer::system const &,
		sge::renderer::device::ffp &,
		sge::renderer::device::index
	);

	~resolution_chooser();

	sge::gui::widget::base &
	widget();
private:
	void
	on_apply();

	sge::renderer::display_mode::container const display_modes_;

	sge::renderer::device::ffp &renderer_;

		sge::gui::widget::choices choices_;

		sge::gui::widget::button apply_button_;

	sge::gui::widget::box_container widget_;

	fcppt::signal::scoped_connection const apply_connection_;
};

}
}
}
}

#endif
