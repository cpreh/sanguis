#ifndef SANGUIS_SERVER_WORLD_UPDATE_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_UPDATE_ENTITY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/entities/doodad_unique_ptr.hpp>
#include <sanguis/server/entities/simple_unique_ptr.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <fcppt/algorithm/update_action_fwd.hpp>


namespace sanguis::server::world
{

class update_entity
{
public:
	explicit
	update_entity(
		sanguis::duration
	);

	fcppt::algorithm::update_action
	operator()(
		sanguis::server::entities::simple_unique_ptr const &
	) const;

	fcppt::algorithm::update_action
	operator()(
		sanguis::server::entities::doodad_unique_ptr const &
	) const;

	fcppt::algorithm::update_action
	operator()(
		sanguis::server::entities::with_id_unique_ptr const &
	) const;
private:
	template<
		typename T
	>
	fcppt::algorithm::update_action
	impl(
		T const &
	) const;

	sanguis::duration elapsed_time_;
};

}

#endif
