#ifndef SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_STATE_HPP_INCLUDED

#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/client/gui/perk/tab_unique_ptr_vector.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/tab.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>


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
	FCPPT_NONMOVABLE(
		state
	);
public:
	state(
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sge::gui::context_ref,
		sge::gui::style::const_reference,
		sanguis::client::perk::state_ref
	);

	~state();

	[[nodiscard]]
	sge::gui::widget::tab &
	widget();
private:
	sanguis::client::gui::perk::tab_unique_ptr_vector tabs_;

	sge::gui::widget::tab main_tab_;
};

}
}
}
}

#endif
