#include "gameover.hpp"

sanguis::client::states::args::gameover::gameover(
	highscore::name_container const &_names,
	highscore::score_type const _score
)
:
	names_(_names),
	score_(_score)
{
}

sanguis::client::highscore::name_container const &
sanguis::client::states::args::gameover::names() const
{
	return names_;
}

sanguis::client::highscore::score_type
sanguis::client::states::args::gameover::score() const
{
	return score_;
}
