#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sge/rucksack/alignment.hpp>


sanguis::gui::widget::reference_alignment_pair::reference_alignment_pair(
	sanguis::gui::widget::reference const _reference,
	sge::rucksack::alignment const _alignment
)
:
	reference_(
		_reference
	),
	alignment_(
		_alignment
	)
{
}

sanguis::gui::widget::reference const
sanguis::gui::widget::reference_alignment_pair::reference() const
{
	return
		reference_;
}

sge::rucksack::alignment
sanguis::gui::widget::reference_alignment_pair::alignment() const
{
	return
		alignment_;
}
