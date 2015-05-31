#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/tiles/area_container_ref.hpp>
#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/draw.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/error_image.hpp>
#include <sanguis/tiles/lower_bound.hpp>
#include <sanguis/tiles/upper_bound.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/store/srgba8.hpp>
#include <sge/image2d/store/view.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/enum_array.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_unsigned.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char **argv
)
try
{
	if(
		argc
		<
		3
		||
		argc
		>
		4
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Usage: ")
			<< argv[0]
			<< FCPPT_TEXT(" <level-name> <output-path> [seed]\n");

		return
			EXIT_FAILURE;
	}

	sge::systems::instance<
		boost::mpl::vector1<
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::image2d(
				sge::media::optional_extension_set()
			)
		)
	);

	sanguis::creator::top_result const result{
		sanguis::creator::generate(
			sanguis::creator::top_parameters{
				sanguis::creator::name{
					fcppt::from_std_string(
						argv[1]
					)
				},
				argc
				==
				4
				?
					sanguis::creator::seed{
						fcppt::extract_from_string_exn<
							sanguis::creator::seed::value_type
						>(
							std::string{
								argv[3]
							}
						)
					}
				:
					fcppt::random::generator::seed_from_chrono<
						sanguis::creator::seed
					>()
				,
				fcppt::algorithm::enum_array_fold<
					sanguis::creator::opening_count_array
				>(
					[](
						sanguis::creator::opening_type
					)
					{
						return
							sanguis::creator::opening_count{
								0u
							};
					}
				),
				sanguis::creator::spawn_boss{
					false
				}
			}
		)
	};

	sanguis::tiles::collection tile_collection{
		sys.image_system()
	};

	sanguis::tiles::cell_container const cells{
		sanguis::tiles::draw(
			result.grid(),
			result.background_grid(),
			tile_collection,
			sanguis::tiles::lower_bound{
				sanguis::tiles::lower_bound::value_type::null()
			},
			sanguis::tiles::upper_bound{
				fcppt::math::dim::to_vector(
					result.grid().size()
				)
			}
		)
	};

	typedef
	sge::image2d::store::srgba8
	store_type;

	store_type store{
		result.grid().size()
		*
		sanguis::creator::tile_size::value
		,
		store_type::mizuiro_color(
			(sge::image::color::init::red() %= 0.)
			(sge::image::color::init::green() %= 0.)
			(sge::image::color::init::blue() %= 1.)
			(sge::image::color::init::alpha() %= 1.)
		)
	};

	typedef
	std::map<
		boost::filesystem::path,
		sge::image2d::file_unique_ptr
	>
	path_file_map;

	path_file_map files;

	typedef
	fcppt::container::enum_array<
		sanguis::tiles::error,
		sge::image2d::store::object
	>
	error_image_array;

	error_image_array const error_images(
		fcppt::algorithm::enum_array_fold<
			error_image_array
		>(
			[](
				sanguis::tiles::error const _error
			)
			{
				return
					sanguis::tiles::error_image(
						_error
					);
			}
		)
	);

	for(
		sanguis::tiles::cell const &cell
		:
		cells
	)
	{
		sge::image2d::vector const dest_pos(
			fcppt::math::vector::structure_cast<
				sge::image2d::rect::vector,
				fcppt::cast::size_fun
			>(
				fcppt::math::vector::to_unsigned(
					cell.pos()
				)
			)
		);

		fcppt::variant::match(
			cell.content(),
			[
				&store,
				&cell,
				&files,
				&sys,
				dest_pos
			](
				sanguis::tiles::area_container_ref const &_container
			)
			{
				sge::image2d::view::const_object const source_view(
					sge::image2d::view::checked_sub(
						fcppt::container::get_or_insert(
							files,
							cell.path().get(),
							[
								&sys
							](
								boost::filesystem::path const &_path
							)
							{
								return
									FCPPT_ASSERT_OPTIONAL_ERROR(
										sys.image_system().load(
											_path
										)
									);
							}
						)->view(),
						FCPPT_ASSERT_OPTIONAL_ERROR(
							fcppt::container::maybe_front(
								_container.get()
							)
						)
					)
				);

				sge::image2d::algorithm::copy_and_convert(
					source_view,
					sge::image2d::view::checked_sub(
						sge::image2d::view::object{
							store.wrapped_view()
						},
						sge::image2d::rect{
							dest_pos,
							sge::image2d::view::size(
								source_view
							)
						}
					),
					sge::image::algorithm::may_overlap::no,
					sge::image::algorithm::uninitialized::no
				);
			},
			[
				&store,
				&error_images,
				dest_pos
			](
				sanguis::tiles::error const _error
			)
			{
				sge::image2d::view::const_object const source_view(
					sge::image2d::store::view(
						error_images[
							_error
						]
					)
				);

				sge::image2d::algorithm::copy_and_convert(
					source_view,
					sge::image2d::view::checked_sub(
						sge::image2d::view::object{
							store.wrapped_view()
						},
						sge::image2d::rect{
							dest_pos,
							sge::image2d::view::size(
								source_view
							)
						}
					),
					sge::image::algorithm::may_overlap::no,
					sge::image::algorithm::uninitialized::no
				);
			}
		);
	}

	sge::image2d::save_from_view(
		sys.image_system(),
		sge::image2d::view::const_object{
			store.const_wrapped_view()
		},
		boost::filesystem::path(
			argv[2]
		)
	);

	return
		EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<< _exception.what()
		<< '\n';

	return
		EXIT_FAILURE;
}
