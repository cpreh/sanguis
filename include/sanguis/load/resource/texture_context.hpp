#ifndef SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURE_CONTEXT_HPP_INCLUDED

#include <sanguis/load/resource/texture_context_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{

class texture_context
{
public:
	texture_context();

	texture_context(
		texture_context_impl_ptr const &
	);

	texture_context_impl_ptr const
	value() const;

	~texture_context();
private:
	texture_context_impl_ptr value_;
};

}
}
}

#endif
