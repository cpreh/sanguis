#ifndef SANGUIS_GUI_MINIMUM_SIZE_AREA_HPP_INCLUDED
#define SANGUIS_GUI_MINIMUM_SIZE_AREA_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>
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
		sanguis::gui::widget::base &,
		sge::rucksack::vector
	);

	SANGUIS_GUI_SYMBOL
	~minimum_size_area();

	SANGUIS_GUI_SYMBOL
	void
	position(
		sge::rucksack::vector
	);

	SANGUIS_GUI_SYMBOL
	void
	relayout();

	SANGUIS_GUI_SYMBOL
	sge::rucksack::rect const
	area() const;
private:
	sge::rucksack::widget::minimum_size layout_;
};

}
}

#endif
