#ifndef SANGUIS_MESSAGES_GAME_STATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_GAME_STATE_HPP_INCLUDED

#include "../game_state.hpp"
#include "base.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

// TODO: this should probably carry an id as well
class game_state : public base {
public:
	game_state();
	explicit game_state(const sanguis::game_state &);

	const sanguis::game_state& state() const;
private:
	sanguis::game_state state_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
