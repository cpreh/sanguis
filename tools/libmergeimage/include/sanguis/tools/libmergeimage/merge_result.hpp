#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_MERGE_RESULT_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_MERGE_RESULT_HPP_INCLUDED

#include <sanguis/model/cell_size.hpp>
#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/merge_result_fwd.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{

class merge_result
{
	FCPPT_NONCOPYABLE(
		merge_result
	);
public:
	merge_result(
		sanguis::model::cell_size,
		sanguis::tools::libmergeimage::image_vector &&
	);

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	merge_result(
		merge_result &&
	)
	noexcept;

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	merge_result &
	operator=(
		merge_result &&
	)
	noexcept;

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	~merge_result();

	[[nodiscard]]
	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	sanguis::model::cell_size
	cell_size() const;

	[[nodiscard]]
	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	sanguis::tools::libmergeimage::image_vector const &
	images() const;
private:
	sanguis::model::cell_size cell_size_;

	sanguis::tools::libmergeimage::image_vector images_;
};

}
}
}

#endif
