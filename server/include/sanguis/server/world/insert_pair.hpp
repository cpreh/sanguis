#ifndef SANGUIS_SERVER_WORLD_INSERT_PAIR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_INSERT_PAIR_HPP_INCLUDED

#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/insert_pair_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class insert_pair
{
	FCPPT_NONCOPYABLE(
		insert_pair
	);
public:
	insert_pair(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	);

	insert_pair(
		insert_pair &&
	);

	insert_pair &
	operator=(
		insert_pair &&
	);

	~insert_pair();

	sanguis::server::entities::unique_ptr &
	entity();

	sanguis::server::entities::insert_parameters const &
	insert_parameters() const;
private:
	sanguis::server::entities::unique_ptr entity_;

	sanguis::server::entities::insert_parameters insert_parameters_;
};

}
}
}

#endif
