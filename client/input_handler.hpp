#ifndef SANGUIS_CLIENT_INPUT_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_INPUT_HANDLER_HPP_INCLUDED

#include <sge/input/key_type.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace client
{

struct player_action;

class input_handler {
public:
	typedef boost::function<void (const player_action&)> post_fun;
	input_handler(const post_fun&);
	void input_callback(const sge::key_pair&);
private:
	void direction_event(const sge::key_pair&);
	void rotation_event(const sge::key_pair&);
	void shooting_event(const sge::key_pair&);
	void weapon_switch_event(const sge::key_pair&);

	const post_fun     post_message;
	sge::key_state     last_x,
	                   last_y;
};

}
}

#endif
