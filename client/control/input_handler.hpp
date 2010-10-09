#ifndef SANGUIS_CLIENT_CONTROL_INPUT_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_INPUT_HANDLER_HPP_INCLUDED

#include "input_handler_fwd.hpp"
#include "player_action_fwd.hpp"
#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/key_state.hpp>
#include <sge/input/processor_ptr.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>

namespace sanguis
{
namespace client
{
namespace control
{

class input_handler
{
public:
	typedef fcppt::function::object<
		void (player_action const &)
	> post_fun;

	explicit input_handler(
		sge::input::processor_ptr,
		post_fun const &
	);

	void
	active(
		bool
	);
	
	void
	input_callback(
		sge::input::key_pair const &
	);
private:
	void
	direction_event(
		sge::input::key_pair const &
	);

	void
	rotation_event(
		sge::input::key_pair const &
	);

	void
	shooting_event(
		sge::input::key_pair const &
	);

	void
	weapon_switch_event(
		sge::input::key_pair const &
	);

	void
	pause_unpause_event(
		sge::input::key_pair const &
	);

	bool active_;

	post_fun const post_message_;

	fcppt::signal::scoped_connection const connection_;

	sge::input::key_state
		last_x_,
		last_y_;
};

}
}
}

#endif
