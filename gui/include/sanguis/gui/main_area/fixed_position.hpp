#ifndef SANGUIS_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED
#define SANGUIS_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/minimum_size.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace main_area
{

class fixed_position
:
	public sanguis::gui::main_area::base
{
	FCPPT_NONCOPYABLE(
		fixed_position
	);
public:
	SANGUIS_GUI_SYMBOL
	fixed_position(
		sanguis::gui::widget::base &,
		sge::rucksack::vector
	);

	SANGUIS_GUI_SYMBOL
	~fixed_position()
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

	sanguis::gui::widget::minimum_size minimum_size_;
};

}
}
}

#endif
