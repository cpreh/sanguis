#ifndef SANGUIS_GAME_STATE_HPP_INCLUDED
#define SANGUIS_GAME_STATE_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace sanguis
{
struct game_state
{
	typedef boost::uint32_t score_type;

	score_type score;

	game_state() {}
	game_state(const score_type score) : score(score) {}
};

template<class Archive> 
inline void serialize(Archive &ar,game_state &p,const unsigned) 
{
	ar & p.score;
}
}

#endif
