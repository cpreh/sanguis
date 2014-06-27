#ifndef SANGUIS_GUI_MINIMUM_SIZE_AREA_HPP_INCLUDED
#define SANGUIS_GUI_MINIMUM_SIZE_AREA_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/gravity_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/viewport_adaptor.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/expander.hpp>
#include <sanguis/gui/widget/minimum_size.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{

class minimum_size_area
{
	FCPPT_NONCOPYABLE(
		minimum_size_area
	);
public:
	SANGUIS_GUI_SYMBOL
	minimum_size_area(
		sge::renderer::device::core &,
		sge::viewport::manager &,
		sanguis::gui::context &,
		sanguis::gui::widget::base &,
		sanguis::gui::gravity
	);

	SANGUIS_GUI_SYMBOL
	~minimum_size_area();

	SANGUIS_GUI_SYMBOL
	void
	relayout();
private:
	sanguis::gui::widget::minimum_size minimum_size_;

	sanguis::gui::widget::expander horizontal_expander_;

	sanguis::gui::widget::expander vertical_expander_;

	sanguis::gui::widget::box_container horizontal_container_;

	sanguis::gui::widget::box_container vertical_container_;

	sanguis::gui::viewport_adaptor viewport_adaptor_;
};

}
}

#endif
