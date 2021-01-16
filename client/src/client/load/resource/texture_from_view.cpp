#include <sanguis/client/load/resource/texture_from_view.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>


sge::texture::const_part_unique_ptr
sanguis::client::load::resource::texture_from_view(
	sge::renderer::device::core_ref const _renderer,
	sge::image2d::view::const_object const &_view
)
{
	return
		fcppt::unique_ptr_to_const(
			fcppt::unique_ptr_to_base<
				sge::texture::part
			>(
				fcppt::make_unique_ptr<
					sge::texture::part_raw_ptr
				>(
					sge::renderer::texture::create_planar_from_view(
						_renderer,
						_view,
						sge::renderer::texture::mipmap::off(),
						sge::renderer::resource_flags_field::null(),
						sge::renderer::texture::emulate_srgb::no
					)
				)
			)
		);
}
