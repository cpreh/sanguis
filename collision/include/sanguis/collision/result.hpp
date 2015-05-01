#ifndef SANGUIS_COLLISION_RESULT_HPP_INCLUDED
#define SANGUIS_COLLISION_RESULT_HPP_INCLUDED

#include <sanguis/collision/result_fwd.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/symbol.hpp>


namespace sanguis
{
namespace collision
{

class result
{
public:
	explicit
	result(
		sanguis::collision::speed
	);

	SANGUIS_COLLISION_SYMBOL
	sanguis::collision::speed const
	speed() const;
private:
	sanguis::collision::speed speed_;
};

}
}

#endif
