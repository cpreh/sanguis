#ifndef SANGUIS_CLIENT_PERK_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_STATE_HPP_INCLUDED

#include "state_fwd.hpp"
#include "change_callback.hpp"
#include "change_function.hpp"
#include "level_callback.hpp"
#include "level_function.hpp"
#include "send_callback.hpp"
#include "tree.hpp"
#include "../level.hpp"
#include "../../perk_type.hpp"
#include <fcppt/container/tree/object_decl.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>

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
		perk::tree const &
	);

	void
	level(
		client::level
	);

	void
	choose_perk(
		sanguis::perk_type::type	
	);

	perk::tree const &
	perks();

	client::level const
	level() const;

	client::level const
	levels_left() const;

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

	client::perk::tree perks_;

	client::level
		current_level_,
		consumed_levels_;
	
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
