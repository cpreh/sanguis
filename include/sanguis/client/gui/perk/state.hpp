#ifndef SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED

#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/tab.hpp>
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
	state(
		sanguis::gui::context &,
		sanguis::client::gui::perk::state const &
	);

	~state();
private:
	sanguis::gui::widget::unique_ptr_vector tabs_;

	sanguis::gui::widget::tab main_tab_;
};

}
}
}
}

#endif
