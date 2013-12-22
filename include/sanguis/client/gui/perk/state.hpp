#ifndef SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED

#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/client/gui/perk/tab_unique_ptr_vector.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/tab.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
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
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::gui::context &,
		sanguis::client::perk::state &
	);

	~state();

	sanguis::gui::widget::tab &
	widget();
private:
	sanguis::client::gui::perk::tab_unique_ptr_vector tabs_;

	sanguis::gui::widget::tab main_tab_;
};

}
}
}
}

#endif
