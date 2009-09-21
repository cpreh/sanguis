#include "texture_context_impl.hpp" 
#include <sge/make_shared_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/renderer/device.hpp>
#include <sge/thread/sleep.hpp>
#include <sge/text.hpp>
#include <sge/time/second.hpp>
#include <boost/bind.hpp>
#include <tr1/functional>

sanguis::load::resource::texture_context_impl::texture_context_impl(
	sge::filesystem::path const &_path,
	sge::renderer::device_ptr const _rend,
	sge::image::loader_ptr const _il,
	sge::renderer::filter::texture const _filter)
:
	task_(
		boost::bind(
			&texture_context_impl::task,
			this,
			_path,
			_il)),
	future_(
		task_.object()),
	thread_(
		std::tr1::ref(
			task_)),
	texture_result_(
		),
	rend_(
		_rend),
	filter_(
		_filter),
	clock_(),
	decay_timer_(
		sge::time::second(
			10),
		sge::time::activation_state::active,
		clock_.callback())
{}

bool sanguis::load::resource::texture_context_impl::update()
{
	if (!future_.has_value())
		return false;
	if (!texture_result_)
		texture_result_.reset( 
			new sge::texture::part_raw(
				rend_->create_texture(
					future_.get()->view(),
					filter_,
					sge::renderer::resource_flags::none)));
	return true;
}

void sanguis::load::resource::texture_context_impl::tick(
	time_type const delta)
{
	clock_.update(
		delta);
}

sge::texture::part_ptr const sanguis::load::resource::texture_context_impl::result()
{
	return texture_result_;
}

void sanguis::load::resource::texture_context_impl::kill()
{
	decay_timer_.activate();
	decay_timer_.reset();
}

void sanguis::load::resource::texture_context_impl::revive()
{
	decay_timer_.deactivate();
}

bool sanguis::load::resource::texture_context_impl::decayed() const
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
	sge::filesystem::path const &_path,
	sge::image::loader_ptr const _il
)
{
	sge::image::file_ptr const p = 
		_il->load(
			_path
		);
	
	return p;
}
