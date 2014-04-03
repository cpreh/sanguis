#ifndef SANGUIS_GUI_WIDGET_EXPANDER_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_EXPANDER_HPP_INCLUDED

#include <sanguis/gui/widget/dummy.hpp>
#include <sanguis/gui/widget/expander_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class expander
:
	public sanguis::gui::widget::dummy
{
	FCPPT_NONCOPYABLE(
		expander
	);
public:
	explicit
	expander(
		sge::rucksack::axis
	);

	~expander()
	override;
};

}
}
}

#endif
