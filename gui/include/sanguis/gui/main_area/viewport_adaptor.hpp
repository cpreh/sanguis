#ifndef SANGUIS_GUI_MAIN_AREA_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SANGUIS_GUI_MAIN_AREA_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace main_area
{

class viewport_adaptor
:
	public sanguis::gui::main_area::base
{
	FCPPT_NONCOPYABLE(
		viewport_adaptor
	);
public:
	SANGUIS_GUI_SYMBOL
	viewport_adaptor(
		sge::renderer::device::core &,
		sge::viewport::manager &,
		sanguis::gui::widget::base &
	);

	SANGUIS_GUI_SYMBOL
	~viewport_adaptor()
	override;

	SANGUIS_GUI_SYMBOL
	void
	relayout()
	override;
private:
	sanguis::gui::widget::base &
	widget()
	override;

	sanguis::gui::widget::base &widget_;

	sge::rucksack::viewport::adaptor impl_;
};

}
}
}

#endif
