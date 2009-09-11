#include "texture_context.hpp"
#include <sge/make_shared_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/image/create_texture.hpp>
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
			_rend,
			_il,
			_filter)),
	future_(
		task_.object()),
	/*thread_(
		boost::ref(
			task_))*/
	debug_result_(
		task(_path,_rend,_il,_filter))
{
	sge::cerr << SGE_TEXT("created texture context for ") << _path.string() << SGE_TEXT("\n");
}

bool sanguis::load::resource::texture_context::update()
{
	/* DEBUG
	if (!future_.has_value())
		return false;
		*/
	return true;
}

sge::texture::part_ptr const sanguis::load::resource::texture_context::result()
{
	return debug_result_;
	/* DEBUG
	return future_.get();
	*/
}

sge::texture::part_ptr const sanguis::load::resource::texture_context::task(
	sge::filesystem::path const &_path,
	sge::renderer::device_ptr const _rend,
	sge::image::loader_ptr const _il,
	sge::renderer::filter::texture const _filter)
{
	sge::cerr << SGE_TEXT("created task thread context for ") << _path.string() << SGE_TEXT("\n");
	sge::texture::part_ptr const p = 
		sge::make_shared_ptr<
			sge::texture::part_raw
		>(
			sge::image::create_texture(
				_path,
				_rend,
				_il,
				_filter,
				sge::renderer::resource_flags::none
			)
		);
	sge::cerr << SGE_TEXT("loaded image ") << _path.string() << SGE_TEXT(" in thread, now returning\n");
	return p;
}
