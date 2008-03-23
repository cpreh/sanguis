#ifndef SANGUIS_GAME_STATE_HPP_INCLUDED
#define SANGUIS_GAME_STATE_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace sanguis
{
struct game_state
{
	boost::uint32_t score;

	game_state() {}
	game_state(const boost::uint32_t score) : score(score) {}
};

template<class Archive> 
inline void serialize(Archive &ar,game_state &p,const unsigned) 
{
	ar & p.score;
}
}

#endif
