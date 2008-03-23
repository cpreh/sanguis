#ifndef SANGUIS_MESSAGES_PLAYER_STATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_STATE_HPP_INCLUDED

#include "../player_state.hpp"
#include "base.hpp"
#include "types.hpp"
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class player_state : public base {
public:
	player_state();
	player_state(
		const entity_id,
		const sanguis::player_state &);

private:
	sanguis::player_state state;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & state;
	}
};

}
}

#endif
