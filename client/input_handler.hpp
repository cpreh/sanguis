#ifndef SANGUIS_CLIENT_INPUT_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_INPUT_HANDLER_HPP_INCLUDED

#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/key_state.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace client
{

struct player_action;

class input_handler {
public:
	typedef boost::function<
		void (player_action const &)
	> post_fun;

	explicit input_handler(
		post_fun const &);
	
	void input_callback(
		sge::input::key_pair const &);
private:
	void direction_event(sge::input::key_pair const &);
	void rotation_event(sge::input::key_pair const &);
	void shooting_event(sge::input::key_pair const &);
	void weapon_switch_event(sge::input::key_pair const &);
	void pause_unpause_event(sge::input::key_pair const &);

	post_fun const post_message;
	sge::input::key_state
		last_x,
		last_y;
};

}
}

#endif
