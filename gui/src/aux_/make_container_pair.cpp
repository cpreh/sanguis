#include <sanguis/gui/aux_/make_container_pair.hpp>
#include <sanguis/gui/aux_/swap_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>


sanguis::gui::widget::reference_alignment_vector
sanguis::gui::aux_::make_container_pair(
	sanguis::gui::widget::reference_alignment_pair const &_first,
	sanguis::gui::widget::reference_alignment_pair const &_second,
	sanguis::gui::aux_::swap_pair const _swap
)
{
	return
		_swap.get()
		?
			sanguis::gui::widget::reference_alignment_vector{
				_second,
				_first
			}
		:
			sanguis::gui::widget::reference_alignment_vector{
				_first,
				_second
			}
		;
}
