#ifndef SANGUIS_CLIENT_PERK_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_STATE_HPP_INCLUDED

#include "state_fwd.hpp"
#include "change_callback.hpp"
#include "change_function.hpp"
#include "choosable_state.hpp"
#include "info.hpp"
#include "level_callback.hpp"
#include "level_function.hpp"
#include "level_map.hpp"
#include "send_callback.hpp"
#include "tree.hpp"
#include "tree_unique_ptr.hpp"
#include "../level.hpp"
#include "../../perk_type.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

class state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	explicit state(
		perk::send_callback const &
	);

	~state();

	void
	perks(
		perk::tree_unique_ptr
	);

	void
	player_level(
		client::level
	);

	bool
	choose_perk(
		sanguis::perk_type::type	
	);

	perk::tree const &
	perks() const;

	client::level const
	player_level() const;

	client::level const
	levels_left() const;

	client::level const
	perk_level(
		sanguis::perk_type::type
	) const;

	perk::level_map const &
	perk_levels() const;

	perk::choosable_state::type
	choosable(
		sanguis::perk_type::type
	) const;

	fcppt::signal::auto_connection
	register_level_change(
		perk::level_callback const &
	);

	fcppt::signal::auto_connection
	register_perks_change(
		perk::change_callback const &
	);
private:
	perk::send_callback const send_callback_;

	typedef fcppt::scoped_ptr<
		perk::tree
	> tree_scoped_ptr;
	
	tree_scoped_ptr perks_;

	client::level
		current_level_,
		consumed_levels_;
	
	mutable perk::level_map perk_levels_;
	
	fcppt::signal::object<
		perk::level_function
	> level_signal_;

	fcppt::signal::object<
		perk::change_function
	> change_signal_;
};

}
}
}

#endif
