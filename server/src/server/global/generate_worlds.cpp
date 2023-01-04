#include <sanguis/exception.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/start_name.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/server/dest_world_id.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/global/dest_world_pair.hpp>
#include <sanguis/server/global/generate_worlds.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/global/world_connection_map.hpp>
#include <sanguis/server/global/world_map.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/random.hpp>
#include <sanguis/server/world/random_seed.hpp>
#include <fcppt/make_int_range.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::global::world_map
sanguis::server::global::generate_worlds(sanguis::server::world::parameters const &_parameters)
{
  sanguis::server::world::map worlds{};

  sanguis::server::global::world_connection_map connections{};

  sanguis::server::world::difficulty difficulty(1U);

  auto const insert_world(
      [&worlds](sanguis::server::world::object_unique_ptr &&_world)
      {
        sanguis::world_id const id{_world->world_id()};

        if(fcppt::not_(worlds.insert(std::make_pair(id, std::move(_world))).second))
        {
          throw sanguis::exception{FCPPT_TEXT("Double insert of worlds!")};
        }
      });

  insert_world(sanguis::server::world::generate(
      _parameters,
      sanguis::world_id(0U),
      sanguis::world_name(FCPPT_TEXT("Start Area")),
      difficulty,
      sanguis::creator::top_parameters(
          fcppt::make_ref(_parameters.log_context()),
          sanguis::creator::start_name(),
          sanguis::server::world::random_seed(_parameters.random_generator()),
          fcppt::enum_::array_init<sanguis::creator::opening_count_array>(
              [](sanguis::creator::opening_type const _type)
              {
                switch (_type)
                {
                case sanguis::creator::opening_type::entry:
                case sanguis::creator::opening_type::exit:
                  return sanguis::creator::opening_count{1U};
                }

                FCPPT_ASSERT_UNREACHABLE;
              }),
          sanguis::creator::spawn_boss{false})));

  sanguis::world_id const num_worlds(10U);

  for (auto const world_id :
       fcppt::make_int_range(sanguis::world_id{1U}, sanguis::world_id{num_worlds.get() + 1U}))
  {
    insert_world(sanguis::server::world::random(
        _parameters,
        fcppt::enum_::array_init<sanguis::creator::opening_count_array>(
            [](sanguis::creator::opening_type const _opening_type)
            {
              switch (_opening_type)
              {
              case sanguis::creator::opening_type::entry:
              case sanguis::creator::opening_type::exit:
                return sanguis::creator::opening_count{1U};
              }

              FCPPT_ASSERT_UNREACHABLE;
            }),
        sanguis::creator::spawn_boss{world_id == sanguis::world_id{1U}},
        world_id,
        difficulty++));

    sanguis::world_id const previous_id(world_id.get() - 1U);

    sanguis::creator::opening const current_opening(
        worlds.at(world_id)->openings()[sanguis::creator::opening_type::entry].at(0U));

    sanguis::creator::opening const previous_opening(
        worlds.at(previous_id)->openings()[sanguis::creator::opening_type::exit].at(0U));

    connections.insert(std::make_pair(
        sanguis::server::global::source_world_pair(
            sanguis::server::source_world_id(previous_id), previous_opening),
        sanguis::server::global::dest_world_pair(
            sanguis::server::dest_world_id(world_id), current_opening)));

    connections.insert(std::make_pair(
        sanguis::server::global::source_world_pair(
            sanguis::server::source_world_id(world_id), current_opening),
        sanguis::server::global::dest_world_pair(
            sanguis::server::dest_world_id(previous_id), previous_opening)));
  }

  // TODO(philipp): Move this out of here
  {
    sanguis::server::world::object &last_world(*worlds.at(num_worlds));

    if (fcppt::not_(last_world
                        .insert(
                            sanguis::server::entities::enemies::create(
                                fcppt::make_ref(_parameters.random_generator()),
                                _parameters.weapon_parameters(),
                                sanguis::creator::enemy_type::reaper,
                                sanguis::creator::enemy_kind::unique,
                                last_world.difficulty(),
                                last_world.environment().load_context(),
                                sanguis::server::entities::spawn_owner(
                                    sanguis::server::entities::auto_weak_link()),
                                sanguis::server::entities::enemies::special_chance(0.F)),
                            sanguis::server::entities::insert_parameters_center(
                                sanguis::server::world::grid_pos_to_center(
                                    last_world.openings()[sanguis::creator::opening_type::exit]
                                        .at(0)
                                        .get())))
                        .has_value()))
    {
      throw sanguis::exception{FCPPT_TEXT("Failed to insert reaper!")};
    }
  }

  return sanguis::server::global::world_map(std::move(worlds), std::move(connections));
}
