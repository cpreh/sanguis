#include <sanguis/load/resource/texture_context_impl.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>

sanguis::load::resource::texture_context_impl::texture_context_impl(
	fcppt::filesystem::path const &_path,
	sge::renderer::device &_rend,
	sge::image2d::system &_il
)
:
	task_(
		std::tr1::bind(
			&texture_context_impl::task,
			this,
			_path,
			fcppt::ref(
				_il
			)
		)
	),
	future_(
		task_.get_future()
	),
	thread_(
		// FIXME: boost::ref doesn't work here!
		std::tr1::ref(
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
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				sge::renderer::texture::create_planar_from_view(
					rend_,
					future_.get()->view(),
					sge::renderer::texture::mipmap::off(),
					sge::renderer::texture::address_mode2(
						sge::renderer::texture::address_mode::clamp
					),
					sge::renderer::resource_flags::none
				)
			);

	return true;
}

sge::texture::part_ptr const
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
	fcppt::filesystem::path const &_path,
	sge::image2d::system &_il
)
{
	return
		_il.load(
			_path
		);
}
