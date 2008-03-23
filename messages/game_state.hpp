#ifndef SANGUIS_MESSAGES_GAME_STATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_GAME_STATE_HPP_INCLUDED

#include "../game_state.hpp"
#include "base.hpp"
#include <sge/string.hpp>
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class game_state : public base {
public:
	game_state() {}
	game_state(const sanguis::game_state &);

private:
	sanguis::game_state state;

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
