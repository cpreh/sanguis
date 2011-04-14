#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include "chooser_fwd.hpp"
#include "../object_fwd.hpp"
#include "../../level.hpp"
#include "../../perk/container.hpp"
#include "../../perk/state_fwd.hpp"
#include "../../../perk_type.hpp"
#include "../../../time_type.hpp"
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class chooser
{
	FCPPT_NONCOPYABLE(
		chooser
	);
public:
	chooser(
		gui::object &,
		client::perk::state &
	);

	~chooser();

	void
	process(
		time_type
	);
private:
	void
	perks(
		client::perk::container const &
	);

	void
	level(
		client::level
	);

	client::perk::state &state_;

	fcppt::signal::scoped_connection const
		perk_connection_,
		level_connection_;

	client::level const
	levels_left() const;

	void
	regenerate_widgets();
};

}
}
}
}

#endif
