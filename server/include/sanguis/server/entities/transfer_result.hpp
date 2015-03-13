#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_RESULT_HPP_INCLUDED

#include <sanguis/server/collision/transfer_result.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class transfer_result
{
public:
	transfer_result();

	explicit
	transfer_result(
		sanguis::server::collision::transfer_result &&
	);

	sanguis::server::collision::transfer_result const &
	collision_result() const;
private:
	sanguis::server::collision::transfer_result collision_result_;
};

}
}
}

#endif
