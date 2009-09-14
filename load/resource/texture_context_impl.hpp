#ifndef SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_IMPL_HPP_INCLUDED

#include "texture_context_fwd.hpp"
#include <sge/thread/future/packaged_task.hpp>
#include <sge/thread/future/shared_object.hpp>
#include <sge/thread/object.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/optional.hpp>
#include <sge/time/unit.hpp>
#include <sge/image/file_fwd.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <sge/texture/part_fwd.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class texture_context_impl
{
SGE_NONCOPYABLE(texture_context_impl)
public:
	texture_context_impl(
		sge::filesystem::path const &,
		sge::renderer::device_ptr,
		sge::image::loader_ptr,
		sge::renderer::filter::texture);
	bool update();
	sge::texture::part_ptr const result();
	void kill();
	void revive();
	bool decayed() const;
	sge::optional<sge::time::unit> const time_of_death() const;
	~texture_context_impl();
private:
	typedef sge::image::file_ptr future_value;
	sge::thread::future::packaged_task<future_value> task_;
	sge::thread::future::shared_object<future_value> future_;
	sge::thread::object thread_;
	sge::texture::part_ptr texture_result_;
	sge::renderer::device_ptr rend_;
	sge::renderer::filter::texture filter_;
	sge::optional<sge::time::unit> time_of_death_;

	future_value const task(
		sge::filesystem::path const &,
		sge::image::loader_ptr);
};
}
}
}

#endif
