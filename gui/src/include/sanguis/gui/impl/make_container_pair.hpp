#ifndef SANGUIS_GUI_IMPL_MAKE_CONTAINER_PAIR_HPP_INCLUDED
#define SANGUIS_GUI_IMPL_MAKE_CONTAINER_PAIR_HPP_INCLUDED

#include <sanguis/gui/impl/swap_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>


namespace sanguis
{
namespace gui
{
namespace impl
{

sanguis::gui::widget::reference_alignment_vector
make_container_pair(
	sanguis::gui::widget::reference_alignment_pair const &,
	sanguis::gui::widget::reference_alignment_pair const &,
	sanguis::gui::impl::swap_pair
);

}
}
}

#endif
