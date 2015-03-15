#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/body_collision_callback.hpp>
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
#include <sanguis/collision/world/position_change_callback.hpp>
#include <sanguis/creator/dim.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


int
main()
{
	sanguis::collision::world::object_unique_ptr const world{
		sanguis::collision::world::create(
			sanguis::collision::world::parameters{
				sanguis::collision::world::body_collision_callback{
					[](
						sanguis::collision::world::body_base &,
						sanguis::collision::world::body_base &
					)
					{
					}
				},
				fcppt::math::dim::fill<
					sanguis::creator::dim
				>(
					100u
				)
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
		boost::logic::tribool const
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
	};

	body_base fake_body_base;

	auto const make_bodies(
		[
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
									sanguis::collision::center{
										sanguis::collision::vector2{
											10.f,
											10.f
										}
									},
									sanguis::collision::speed{
										sanguis::collision::vector2::null()
									},
									sanguis::collision::radius{
										50.f
									},
									sanguis::collision::world::position_change_callback{
										[](
											sanguis::collision::center
										)
										{
										}
									},
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
				world->activate_body(
					*body,
					sanguis::collision::world::created{
						true
					}
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
								sanguis::collision::vector2{
									10.f,
									10.f
								}
							},
							sanguis::collision::radius{
								2000.f
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

	fcppt::algorithm::repeat(
		100,
		[
			&world
		]
		{
			world->update(
				sanguis::collision::duration(
					0.06f
				)
			);
		}
	);
}
