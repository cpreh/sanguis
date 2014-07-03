#ifndef SANGUIS_GUI_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SANGUIS_GUI_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sanguis/gui/main_area.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{

class viewport_adaptor
:
	public sanguis::gui::main_area
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

	sge::rucksack::widget::viewport_adaptor impl_;
};

}
}

#endif
