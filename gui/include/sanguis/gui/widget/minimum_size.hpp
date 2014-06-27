#ifndef SANGUIS_GUI_WIDGET_MINIMUM_SIZE_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_MINIMUM_SIZE_HPP_INCLUDED

#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/dummy.hpp>
#include <sanguis/gui/widget/minimum_size_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class minimum_size
:
	public sanguis::gui::widget::dummy
{
	FCPPT_NONCOPYABLE(
		minimum_size
	);
public:
	explicit
	minimum_size(
		sanguis::gui::widget::base &
	);

	~minimum_size()
	override;
private:
	sge::rucksack::widget::base &
	layout()
	override;

	sge::rucksack::widget::minimum_size layout_;
};

}
}
}

#endif
