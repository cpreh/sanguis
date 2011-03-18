#include "texture_context_impl.hpp" 
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/file.hpp>
#include <sge/renderer/device.hpp>
#include <sge/time/second.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>

sanguis::load::resource::texture_context_impl::texture_context_impl(
	fcppt::filesystem::path const &_path,
	sge::renderer::device_ptr const _rend,
	sge::image2d::multi_loader &_il,
	sge::renderer::texture::filter::object const &_filter
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
		fcppt::ref(
			task_
		)
	),
	texture_result_(),
	rend_(
		_rend
	),
	filter_(
		_filter
	),
	clock_(),
	decay_timer_(
		sge::time::second(
			10
		),
		sge::time::activation_state::active,
		clock_.callback()
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
					filter_,
					sge::renderer::texture::address_mode2(
						sge::renderer::texture::address_mode::clamp
					),
					sge::renderer::resource_flags::none
				)
			);

	return true;
}

void
sanguis::load::resource::texture_context_impl::tick(
	time_type const _delta
)
{
	clock_.update(
		_delta
	);
}

sge::texture::part_ptr const
sanguis::load::resource::texture_context_impl::result()
{
	return texture_result_;
}

void
sanguis::load::resource::texture_context_impl::kill()
{
	decay_timer_.activate();

	decay_timer_.reset();
}

void
sanguis::load::resource::texture_context_impl::revive()
{
	decay_timer_.deactivate();
}

bool
sanguis::load::resource::texture_context_impl::decayed() const
{
	return 
		decay_timer_.active() && decay_timer_.expired();
}

sanguis::load::resource::texture_context_impl::~texture_context_impl()
{
	thread_.join();
}

sanguis::load::resource::texture_context_impl::future_value const
sanguis::load::resource::texture_context_impl::task(
	fcppt::filesystem::path const &_path,
	sge::image2d::multi_loader &_il
)
{
	return
		_il.load(
			_path
		);
}
