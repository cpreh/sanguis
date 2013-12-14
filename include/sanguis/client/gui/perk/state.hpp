#ifndef SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED

#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/unique_ptr_vector.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state();

	~state();
private:
	sanguis::gui::widget::unique_ptr_vector top_buttons_;

	sanguis::gui::widget::box_container top_buttons_widget_;

	sanguis::gui::widget::box_container main_box_;
};

}
}
}
}

#endif
