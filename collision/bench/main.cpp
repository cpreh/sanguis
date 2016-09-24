#include <sanguis/log_level_streams.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/log.hpp>
#include <sanguis/collision/optional_mass.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/create.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_base.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/object_unique_ptr.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/collision/world/update_result.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/tile.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/cast/to_void.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


int
main()
{
	sanguis::creator::grid const grid(
		fcppt::math::dim::fill<
			sanguis::creator::dim
		>(
			100u
		),
		sanguis::creator::tile::nothing
	);

	sanguis::collision::world::object_unique_ptr const world{
		sanguis::collision::world::create(
			sanguis::collision::world::parameters{
				grid
			}
		)
	};

	typedef
	std::vector<
		sanguis::collision::world::body_unique_ptr
	>
	body_container;

	typedef
	std::vector<
		sanguis::collision::world::ghost_unique_ptr
	>
	ghost_container;

	class body_base
	:
		public sanguis::collision::world::body_base
	{
		FCPPT_NONCOPYABLE(
			body_base
		);
	public:
		body_base()
		{
		}

		~body_base()
		override
		{
		}
	private:
		boost::logic::tribool
		can_collide_with(
			sanguis::collision::world::body_base const &
		) const
		override
		{
			return
				boost::logic::indeterminate;
		}

		void
		collision(
			sanguis::collision::world::body_base &
		)
		override
		{
		}

		void
		center_changed(
			sanguis::collision::center
		)
		override
		{
		}

		void
		speed_changed(
			sanguis::collision::speed
		)
		override
		{
		}

		void
		world_collision()
		override
		{
		}
	};

	fcppt::log::context log_context{
		fcppt::log::optional_level{
			fcppt::log::level::error
		},
		sanguis::log_level_streams()
	};

	sanguis::collision::log const log{
		log_context
	};

	body_base fake_body_base;

	auto const make_bodies(
		[
			&log,
			&world,
			&fake_body_base
		](
			unsigned const _count,
			sanguis::collision::world::body_group const _group
		)
		{
			return
				fcppt::algorithm::map<
					body_container
				>(
					fcppt::make_int_range_count(
						_count
					),
					[
						&log,
						&world,
						&fake_body_base,
						_group
					](
						unsigned
					)
					{
						return
							world->create_body(
								sanguis::collision::world::body_parameters{
									log,
									sanguis::collision::center{
										fcppt::math::vector::fill<
											sanguis::collision::length2
										>(
											fcppt::literal<
												sanguis::collision::unit
											>(
												10
											)
											*
											boost::units::si::meter
										)
									},
									fcppt::math::vector::fill<
										sanguis::collision::speed
									>(
										fcppt::literal<
											sanguis::collision::unit
										>(
											0
										)
										*
										boost::units::si::meter_per_second
									),
									sanguis::collision::radius{
										fcppt::literal<
											sanguis::collision::unit
										>(
											50
										)
										*
										boost::units::si::meter
									},
									sanguis::collision::optional_mass(),
									_group,
									fake_body_base
								}
							);
					}
				);
		}
	);

	auto const activate_bodies(
		[
			&world
		](
			body_container const &_bodies
		)
		{
			for(
				sanguis::collision::world::body_unique_ptr const &body
				:
				_bodies
			)
				fcppt::cast::to_void(
					world->activate_body(
						*body,
						sanguis::collision::world::created{
							true
						}
					)
				);
		}
	);

	body_container const enemies(
		make_bodies(
			1000,
			sanguis::collision::world::body_group::enemy
		)
	);

	body_container const players(
		make_bodies(
			10,
			sanguis::collision::world::body_group::player
		)
	);

	class ghost_base
	:
		public sanguis::collision::world::ghost_base
	{
		FCPPT_NONCOPYABLE(
			ghost_base
		);
	public:
		ghost_base()
		{
		}

		~ghost_base()
		override
		{
		}
	};

	ghost_base fake_ghost_base;

	ghost_container const ghosts(
		fcppt::algorithm::map<
			ghost_container
		>(
			fcppt::make_int_range_count(
				1000
			),
			[
				&world,
				&fake_ghost_base
			](
				int
			)
			{
				return
					world->create_ghost(
						sanguis::collision::world::ghost_parameters(
							sanguis::collision::center{
								fcppt::math::vector::fill<
									sanguis::collision::length2
								>(
									fcppt::literal<
										sanguis::collision::unit
									>(
										10
									)
									*
									boost::units::si::meter
								)
							},
							sanguis::collision::radius{
								fcppt::literal<
									sanguis::collision::unit
								>(
									2000
								)
								*
								boost::units::si::meter
							},
							sanguis::collision::world::ghost_group::player_sight,
							fake_ghost_base
						)
					);
			}
		)
	);

	activate_bodies(
		enemies
	);

	activate_bodies(
		players
	);

	for(
		auto const &ghost
		:
		ghosts
	)
		fcppt::cast::to_void(
			world->activate_ghost(
				*ghost
			)
		);

	fcppt::algorithm::repeat(
		100,
		[
			&world
		]
		{
			sanguis::collision::world::update_result const result(
				world->update(
					sanguis::collision::duration(
						0.06f
					)
				)
			);
		}
	);
}
