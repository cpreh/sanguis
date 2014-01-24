#ifndef SANGUIS_GUI_FIXED_AREA_HPP_INCLUDED
#define SANGUIS_GUI_FIXED_AREA_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sge/rucksack/rect_fwd.hpp>
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
		sge::rucksack::rect,
		sge::rucksack::widget::base &
	);

	SANGUIS_GUI_SYMBOL
	~fixed_area();
};

}
}

#endif
