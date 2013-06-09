#ifndef SANGUIS_SERVER_COLLISION_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_RESULT_HPP_INCLUDED

#include <sanguis/server/center.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/result_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

class result
{
public:
	result(
		sanguis::server::speed const &,
		sanguis::server::center const &
	);

	sanguis::server::speed const &
	speed() const;

	sanguis::server::center const &
	center() const;
private:
	sanguis::server::speed speed_;

	sanguis::server::center center_;
};

}
}
}

#endif
