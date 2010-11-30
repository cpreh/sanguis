#include "player_record.hpp"

sanguis::server::player_record::player_record(
	fcppt::string const &_name,
	exp_type const _exp
)
:
	name_(_name),
	exp_(_exp)
{}
	
fcppt::string const &
sanguis::server::player_record::name() const
{
	return name_;
}

sanguis::server::exp_type
sanguis::server::player_record::exp() const
{
	return exp_;
}
