#include <sanguis/load/resource/texture_context_impl.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/renderer/device/core.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

sanguis::load::resource::texture_context_impl::texture_context_impl(
	boost::filesystem::path const &_path,
	sge::renderer::device::core &_rend,
	sge::image2d::system &_il
)
:
	task_(
		std::bind(
			&texture_context_impl::task,
			this,
			_path,
			std::ref(
				_il
			)
		)
	),
	future_(
		task_.get_future()
	),
	thread_(
		std::ref(
			task_
		)
	),
	texture_result_(),
	rend_(
		_rend
	)
{
}

bool
sanguis::load::resource::texture_context_impl::update()
{
	if(
		!future_.has_value()
	)
		return false;

	if(
		!texture_result_
	)
		texture_result_ =
			sge::renderer::texture::planar_shared_ptr(
				sge::renderer::texture::create_planar_from_view(
					rend_,
					future_.get()->view(),
					sge::renderer::texture::mipmap::off(),
					sge::renderer::resource_flags_field::null(),
					sge::renderer::texture::emulate_srgb::yes
				)
			);

	return true;
}

sge::renderer::texture::planar_shared_ptr const
sanguis::load::resource::texture_context_impl::result()
{
	return texture_result_;
}

sanguis::load::resource::texture_context_impl::~texture_context_impl()
{
	thread_.join();
}

sanguis::load::resource::texture_context_impl::future_value const
sanguis::load::resource::texture_context_impl::task(
	boost::filesystem::path const &_path,
	sge::image2d::system &_il
)
{
	return
		sanguis::load::resource::texture_context_impl::future_value(
			_il.load(
				_path
			)
		);
}
