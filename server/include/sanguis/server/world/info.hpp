#ifndef SANGUIS_SERVER_WORLD_INFO_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_INFO_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/server/world/info_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class info
{
public:
	info(
		sanguis::world_id,
		sanguis::world_name &&,
		sanguis::creator::seed,
		sanguis::creator::name &&,
		sanguis::creator::spawn_boss,
		sanguis::creator::opening_container_array &&
	);

	[[nodiscard]]
	sanguis::world_id
	world_id() const;

	[[nodiscard]]
	sanguis::world_name const &
	world_name() const;

	[[nodiscard]]
	sanguis::creator::seed
	seed() const;

	[[nodiscard]]
	sanguis::creator::name const &
	generator_name() const;

	[[nodiscard]]
	sanguis::creator::spawn_boss
	spawn_boss() const;

	[[nodiscard]]
	sanguis::creator::opening_container_array const &
	openings() const;
private:
	sanguis::world_id world_id_;

	sanguis::world_name world_name_;

	sanguis::creator::seed seed_;

	sanguis::creator::name generator_name_;

	sanguis::creator::spawn_boss spawn_boss_;

	sanguis::creator::opening_container_array openings_;
};

}
}
}

#endif
