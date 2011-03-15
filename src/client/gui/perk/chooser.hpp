#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include "chooser_fwd.hpp"
#include "send_callback.hpp"
#include "../object_fwd.hpp"
#include "../../level_type.hpp"
#include "../../perk_container.hpp"
#include "../../../perk_type.hpp"
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>

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
		perk::send_callback const &
	);

	~chooser();

	void
	process();

	void
	perks(
		client::perk_container const &
	);

	void
	level_up(
		client::level_type
	);

	bool
	activated() const;

	void
	activated(
		bool
	);
private:
	client::perk_container perks_;

	client::level_type 
		current_level_,
		consumed_levels_;

	fcppt::signal::connection_manager const connections_;

	perk::send_callback const send_callback_;

	level_type
	levels_left() const;

	void
	regenerate_label();

	void
	regenerate_widgets();

	void
	choose_callback(
		perk_type::type
	);

	void
	consume_level();
};

}
}
}
}

#endif
