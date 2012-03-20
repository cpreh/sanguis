#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/envelope.hpp>
#include <sanguis/client/draw2d/scene/world/make_batch.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/creator/generator/generate.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sanguis/creator/geometry/rect.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <fcppt/algorithm/array_map.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::scene::world::batch_grid_unique_ptr
sanguis::client::draw2d::scene::world::generate_batches(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	sanguis::creator::generator::top_parameters const &_parameters,
	load::resource::textures const &_textures
)
{
	sanguis::creator::generator::result const generated(
		sanguis::creator::generator::generate(
			_parameters
		)
	);

	world::batch_grid_unique_ptr ret(
		fcppt::make_unique_ptr<
			world::batch_grid
		>(
			fcppt::math::dim::structure_cast<
				world::batch_grid::dim
			>(
				fcppt::algorithm::array_map<
					sanguis::creator::generator::size
				>(
					generated.size(),
					std::tr1::bind(
						fcppt::math::ceil_div<
							sanguis::creator::generator::size::value_type
						>,
						std::tr1::placeholders::_1,
						world::batch_size
					)
				)
			)
		)
	);

	sanguis::creator::geometry::shape_container const &shapes(
		generated.shapes()
	);

	typedef fcppt::container::grid::object<
		sanguis::creator::geometry::shape_container,
		2
	> shape_container_grid;

	shape_container_grid temp_grid(
		ret->size()
	);

	for(
		sanguis::creator::geometry::shape_container::const_iterator shape_it(
			shapes.begin()
		);
		shape_it != shapes.end();
		++shape_it
	)
	{
		sanguis::creator::geometry::rect const envelope(
			world::envelope(
				shape_it->polygon()
			)
		);

		sanguis::creator::geometry::rect::dim const batch_dim(
			fcppt::math::dim::fill<
				sanguis::creator::geometry::rect::dim::dim_wrapper::value
			>(
				world::batch_size
			)
		);

		sanguis::creator::geometry::vector const
			lower_bound(
				envelope.pos()
				/
				batch_dim
			),
			upper_bound(
				(
					envelope.pos()
					+ envelope.size()
				)
				/ batch_dim
			);
#if 0
		sanguis::creator::geometry::polygon const &poly(
			shape_it->polygon()
		);

		typedef std::vector<
			sanguis::creator::geometry::vector
		> vector2_container;

		vector2_container converted;

		converted.reserve(
			poly.size()
		);

		sge::projectile::shape::triangle_set const new_triangles(
			sge::projectile::triangulation::triangulate<
				sge::projectile::shape::triangle_set
			>(
				converted,
				0.01f // TODO!
			)
		);
#endif
		// TODO: we need better iteration mechanisms for grid!
		for(
			sanguis::creator::geometry::vector::value_type pos_y(
				lower_bound.y()
			);
			pos_y <= upper_bound.y();
			++pos_y
		)
			for(
				sanguis::creator::geometry::vector::value_type pos_x(
					lower_bound.x()
				);
				pos_x <= upper_bound.x();
				++pos_x
			)
			{
				shape_container_grid::dim const pos(
					pos_x,
					pos_y
				);

				if(
					!fcppt::container::grid::in_range(
						temp_grid,
						pos
					)
				)
					throw sanguis::exception(
						(
							fcppt::format(
								FCPPT_TEXT("Tried to insert a shape at position %1%,")
								FCPPT_TEXT(" but the grid size is only %2%!")
							)
							% pos
							% temp_grid.size()
						).str()
					);

				temp_grid[
					pos
				].push_back(
					*shape_it
				);
			}
	}

	for(
		shape_container_grid::const_iterator it(
			temp_grid.begin()
		);
		it != temp_grid.end();
		++it
	)
		*(
			ret->begin() +
			std::distance(
				static_cast<
					shape_container_grid const &
				>(
					temp_grid
				).begin(),
				it
			)
		) =
			world::make_batch(
				_renderer,
				_vertex_declaration,
				_textures,
				*it
			);

	return
		fcppt::move(
			ret
		);
}
