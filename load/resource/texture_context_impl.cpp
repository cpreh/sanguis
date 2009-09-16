#include "texture_context_impl.hpp" 
#include <sge/make_shared_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/renderer/device.hpp>
#include <sge/thread/sleep.hpp>
#include <sge/cout.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <sge/time/time.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

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
		boost::ref(
			task_)),
	texture_result_(
		),
	rend_(
		_rend),
	filter_(
		_filter),
	time_of_death_(
		sge::optional<sge::time::unit>())
{
	sge::cerr << SGE_TEXT("created texture context for ") << _path.string() << SGE_TEXT("\n");
}

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

sge::texture::part_ptr const sanguis::load::resource::texture_context_impl::result()
{
	return texture_result_;
}

void sanguis::load::resource::texture_context_impl::kill()
{
	time_of_death_ = 
		sge::time::time();
}

void sanguis::load::resource::texture_context_impl::revive()
{
	time_of_death_.reset();
}

bool sanguis::load::resource::texture_context_impl::decayed() const
{
	if (!time_of_death_)
		return false;
	//sge::cout << "time diff is " << ((sge::time::time() - *time_of_death_)/sge::time::hz()) << "\n";
	return 
		(sge::time::time() - *time_of_death_)/sge::time::hz() > 10;
}

sge::optional<sge::time::unit> const sanguis::load::resource::texture_context_impl::time_of_death() const
{
	return time_of_death_;
}

sanguis::load::resource::texture_context_impl::~texture_context_impl()
{
	thread_.join();
}

sanguis::load::resource::texture_context_impl::future_value const sanguis::load::resource::texture_context_impl::task(
	sge::filesystem::path const &_path,
	sge::image::loader_ptr const _il)
{
	sge::cerr << SGE_TEXT("created task thread context for ") << _path.string() << SGE_TEXT("\n");
	//sge::thread::sleep( DEBUG
	//	3);
	sge::image::file_ptr const p = 
		_il->load(
			_path);
	sge::cerr << SGE_TEXT("loaded image ") << _path.string() << SGE_TEXT(" in thread, now returning\n");
	return p;
}
