#ifndef SANGUIS_GUI_AUX__MAKE_CONTAINER_PAIR_HPP_INCLUDED
#define SANGUIS_GUI_AUX__MAKE_CONTAINER_PAIR_HPP_INCLUDED

#include <sanguis/gui/aux_/swap_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{

sanguis::gui::widget::reference_alignment_vector
make_container_pair(
	sanguis::gui::widget::reference_alignment_pair const &,
	sanguis::gui::widget::reference_alignment_pair const &,
	sanguis::gui::aux_::swap_pair
);

}
}
}

#endif
