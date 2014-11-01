#ifndef SANGUIS_SERVER_WORLD_UPDATE_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_UPDATE_ENTITY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/entities/doodad_unique_ptr.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class update_entity
{
	FCPPT_NONASSIGNABLE(
		update_entity
	);
public:
	explicit
	update_entity(
		sanguis::duration
	);

	bool
	operator()(
		sanguis::server::entities::unique_ptr const &
	) const;

	bool
	operator()(
		sanguis::server::entities::doodad_unique_ptr const &
	) const;

	bool
	operator()(
		sanguis::server::entities::with_id_unique_ptr const &
	) const;
private:
	template<
		typename T
	>
	bool
	impl(
		T const &
	) const;

	sanguis::duration const elapsed_time_;
};

}
}
}

#endif
