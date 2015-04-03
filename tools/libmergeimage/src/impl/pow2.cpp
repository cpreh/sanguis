#include <sanguis/tools/libmergeimage/impl/pow2.hpp>
#include <sge/image/size_type.hpp>
#include <fcppt/literal.hpp>


sge::image::size_type
sanguis::tools::libmergeimage::impl::pow2(
	sge::image::size_type const _exp
)
{
	return
		fcppt::literal<
			sge::image::size_type
		>(
			1u
		)
		<<
		_exp;
}
