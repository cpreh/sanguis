#include "entry.hpp"

sanguis::client::highscore::entry::entry()
:
	names_(),
	score_()
{
}

sanguis::client::highscore::entry::entry(
	name_container const &_names,
	score_type const _score)
:
	names_(_names),
	score_(_score)
{
}

sanguis::client::highscore::name_container const &
sanguis::client::highscore::entry::names() const
{
	return names_;
}

sanguis::client::highscore::score_type 
sanguis::client::highscore::entry::score() const
{
	return score_;
}

