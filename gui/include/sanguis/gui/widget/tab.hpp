#ifndef SANGUIS_GUI_WIDGET_TAB_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_TAB_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/reference_name_vector.hpp>
#include <sanguis/gui/widget/tab_fwd.hpp>
#include <sanguis/gui/widget/unique_ptr_vector.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class tab
:
	public sanguis::gui::widget::box_container
{
	FCPPT_NONCOPYABLE(
		tab
	);
public:
	SANGUIS_GUI_SYMBOL
	tab(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::gui::context &,
		sanguis::gui::widget::reference_name_vector const &
	);

	SANGUIS_GUI_SYMBOL
	~tab()
	override;
private:
	sanguis::gui::widget::unique_ptr_vector top_buttons_;

	sanguis::gui::widget::box_container top_buttons_box_;
};

}
}
}

#endif
