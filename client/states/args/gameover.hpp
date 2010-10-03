#ifndef SANGUIS_CLIENT_STATES_ARGS_GAMEOVER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_ARGS_GAMEOVER_HPP_INCLUDED

#include "gameover_fwd.hpp"
#include "../../highscore/name_container.hpp"
#include "../../highscore/score_type.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace client
{
namespace states
{
namespace args
{

class gameover
{
	FCPPT_NONASSIGNABLE(
		gameover
	)
public:
	gameover(
		highscore::name_container const &,
		highscore::score_type
	);

	highscore::name_container const &
	names() const;

	highscore::score_type
	score() const;
private:
	highscore::name_container const names_;

	highscore::score_type const score_;
};

}
}
}
}

#endif
