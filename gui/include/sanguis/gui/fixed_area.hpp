#ifndef SANGUIS_GUI_FIXED_AREA_HPP_INCLUDED
#define SANGUIS_GUI_FIXED_AREA_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{

class fixed_area
{
	FCPPT_NONCOPYABLE(
		fixed_area
	);
public:
	SANGUIS_GUI_SYMBOL
	fixed_area(
		sanguis::gui::widget::base &,
		sge::rucksack::rect
	);

	SANGUIS_GUI_SYMBOL
	~fixed_area();

	SANGUIS_GUI_SYMBOL
	void
	position(
		sge::rucksack::vector
	);

	SANGUIS_GUI_SYMBOL
	sge::rucksack::rect const
	area() const;
private:
	sge::rucksack::widget::base &layout_;
};

}
}

#endif
