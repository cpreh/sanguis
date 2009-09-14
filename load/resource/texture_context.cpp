#include "texture_context.hpp" 
#include <sge/make_shared_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/renderer/device.hpp>
#include <sge/thread/sleep.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

sanguis::load::resource::texture_context::texture_context(
	sge::filesystem::path const &_path,
	sge::renderer::device_ptr const _rend,
	sge::image::loader_ptr const _il,
	sge::renderer::filter::texture const _filter)
:
	task_(
		boost::bind(
			&texture_context::task,
			this,
			_path,
			_il)),
	future_(
		task_.object()),
	thread_(
		boost::ref(
			task_)),
	texture_result_(
		),
	rend_(
		_rend),
	filter_(
		_filter)
{
	sge::cerr << SGE_TEXT("created texture context for ") << _path.string() << SGE_TEXT("\n");
}

bool sanguis::load::resource::texture_context::update()
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

sge::texture::part_ptr const sanguis::load::resource::texture_context::result()
{
	return texture_result_;
}

sanguis::load::resource::texture_context::~texture_context()
{
	thread_.join();
}

sanguis::load::resource::texture_context::future_value const sanguis::load::resource::texture_context::task(
	sge::filesystem::path const &_path,
	sge::image::loader_ptr const _il)
{
	sge::cerr << SGE_TEXT("created task thread context for ") << _path.string() << SGE_TEXT("\n");
	sge::thread::sleep(
		3);
	sge::image::file_ptr const p = 
		_il->load(
			_path);
	sge::cerr << SGE_TEXT("loaded image ") << _path.string() << SGE_TEXT(" in thread, now returning\n");
	return p;
}
