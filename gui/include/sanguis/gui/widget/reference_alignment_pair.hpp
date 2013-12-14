#ifndef SANGUIS_GUI_WIDGET_REFERENCE_ALIGNMENT_PAIR_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_REFERENCE_ALIGNMENT_PAIR_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair_fwd.hpp>
#include <sge/rucksack/alignment.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class reference_alignment_pair
{
public:
	SANGUIS_GUI_SYMBOL
	reference_alignment_pair(
		sanguis::gui::widget::reference,
		sge::rucksack::alignment
	);

	sanguis::gui::widget::reference const
	reference() const;

	sge::rucksack::alignment
	alignment() const;
private:
	sanguis::gui::widget::reference reference_;

	sge::rucksack::alignment alignment_;
};

}
}
}

#endif
