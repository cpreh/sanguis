#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/make_batch.hpp>
#include <sanguis/client/draw2d/scene/world/sort_shapes.hpp>
#include <sanguis/client/draw2d/scene/world/texture_slice.hpp>
#include <sanguis/client/draw2d/scene/world/texture_slice_vector.hpp>
#include <sanguis/client/draw2d/scene/world/vf/format_part.hpp>
#include <sanguis/client/draw2d/scene/world/vf/pos.hpp>
#include <sanguis/client/draw2d/scene/world/vf/texpos.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/shape.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_shared_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/arithmetic.hpp>
#include <algorithm>
#include <numeric>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::renderer::vertex::count const
poly_count(
	sanguis::creator::geometry::shape const &_shape
)
{
	return
		sge::renderer::vertex::count(
			_shape.polygon().size()
		);
}

}

sanguis::client::draw2d::scene::world::batch const
sanguis::client::draw2d::scene::world::make_batch(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sanguis::load::resource::textures const &_textures,
	sanguis::creator::geometry::shape_container _shapes
)
{
	if(
		_shapes.empty()
	)
		return
			sanguis::client::draw2d::scene::world::batch(
				sge::renderer::vertex::buffer_shared_ptr(),
				sanguis::client::draw2d::scene::world::texture_slice_vector()
			);

	std::sort(
		_shapes.begin(),
		_shapes.end(),
		sanguis::client::draw2d::scene::world::sort_shapes
	);

	sge::renderer::vertex::buffer_shared_ptr const vertex_buffer(
		_renderer.create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				_vertex_declaration,
				sge::renderer::vf::dynamic::part_index(
					0u
				),
				std::accumulate(
					_shapes.begin(),
					_shapes.end(),
					sge::renderer::vertex::count(
						0u
					),
					boost::phoenix::arg_names::arg1 +=
						boost::phoenix::bind(
							poly_count,
							boost::phoenix::arg_names::arg2
						)
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	sanguis::client::draw2d::scene::world::texture_slice_vector texture_slices;

	sge::renderer::vertex::scoped_lock const vblock(
		*vertex_buffer,
		sge::renderer::lock_mode::writeonly
	);

	typedef sge::renderer::vf::view<
		sanguis::client::draw2d::scene::world::vf::format_part
	> vf_view;

	vf_view const vertices(
		vblock.value()
	);

	vf_view::iterator vb_it(
		vertices.begin()
	);

	sge::renderer::size_type cur_vertex(0u);

	sanguis::creator::geometry::texture_name cur_texture(
		_shapes[0].texture_name()
	);

	sge::renderer::size_type num_vertices(0u);

	for(
		sanguis::creator::geometry::shape_container::const_iterator shape_it(
			_shapes.begin()
		);
		shape_it != _shapes.end();
		++shape_it
	)
	{
		sanguis::creator::geometry::polygon const &poly(
			shape_it->polygon()
		);

		for(
			sanguis::creator::geometry::polygon::const_iterator poly_it(
				poly.begin()
			);
			poly_it != poly.end();
			++poly_it
		)
		{
			(*vb_it).set<
				sanguis::client::draw2d::scene::world::vf::pos
			>(
				fcppt::math::vector::structure_cast<
					sanguis::client::draw2d::scene::world::vf::pos::packed_type
				>(
					poly_it->pos()
				)
			);

			(*vb_it).set<
				sanguis::client::draw2d::scene::world::vf::texpos
			>(
				fcppt::math::vector::structure_cast<
					sanguis::client::draw2d::scene::world::vf::texpos::packed_type
				>(
					poly_it->texcoords()
				)
			);

			++vb_it;
		}

		if(
			shape_it->texture_name()
			!= cur_texture
		)
		{
			texture_slices.push_back(
				sanguis::client::draw2d::scene::world::texture_slice(
					sge::renderer::vertex::first(
						cur_vertex
					),
					sge::renderer::vertex::count(
						num_vertices
					),
					_textures.load(
						cur_texture.get() // TODO!
					)
				)
			);

			cur_texture = shape_it->texture_name();

			cur_vertex += num_vertices;

			num_vertices = 0;
		}

		num_vertices += poly.size();
	}

	texture_slices.push_back(
		sanguis::client::draw2d::scene::world::texture_slice(
			sge::renderer::vertex::first(
				cur_vertex
			),
			sge::renderer::vertex::count(
				num_vertices
			),
			_textures.load(
				cur_texture.get()
			)
		)
	);

	return
		sanguis::client::draw2d::scene::world::batch(
			vertex_buffer,
			texture_slices
		);
}
