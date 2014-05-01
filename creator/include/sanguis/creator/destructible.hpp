#ifndef SANGUIS_CREATOR_DESTRUCTIBLE_HPP_INCLUDED
#define SANGUIS_CREATOR_DESTRUCTIBLE_HPP_INCLUDED

#include <sanguis/creator/destructible_fwd.hpp>
#include <sanguis/creator/destructible_pos.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/creator/symbol.hpp>


namespace sanguis
{
namespace creator
{

class destructible
{
public:
	destructible(
		sanguis::creator::destructible_pos,
		sanguis::creator::destructible_type
	);

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::destructible_pos const
	pos() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::destructible_type
	type() const;
private:
	sanguis::creator::destructible_pos pos_;

	sanguis::creator::destructible_type type_;
};

}
}

#endif
