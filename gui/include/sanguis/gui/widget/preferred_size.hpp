#ifndef SANGUIS_GUI_WIDGET_PREFERRED_SIZE_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_PREFERRED_SIZE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/dummy.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class preferred_size
:
	public sanguis::gui::widget::dummy
{
	FCPPT_NONCOPYABLE(
		preferred_size
	);
public:
	SANGUIS_GUI_SYMBOL
	explicit
	preferred_size(
		sge::rucksack::dim const &
	);

	SANGUIS_GUI_SYMBOL
	~preferred_size()
	override;

	sge::rucksack::widget::base &
	layout()
	override;
private:
	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif

