#ifndef SANGUIS_SERVER_WORLD_INSERT_PAIR_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_INSERT_PAIR_DECL_HPP_INCLUDED

#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/world/insert_pair_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

template<
	typename Type
>
class insert_pair
{
	FCPPT_NONCOPYABLE(
		insert_pair
	);
public:
	using
	unique_ptr
	=
	fcppt::unique_ptr<
		Type
	>;

	insert_pair(
		unique_ptr &&,
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

	unique_ptr &
	entity();

	sanguis::server::entities::insert_parameters const &
	insert_parameters() const;
private:
	unique_ptr entity_;

	sanguis::server::entities::insert_parameters insert_parameters_;
};

}
}
}

#endif
