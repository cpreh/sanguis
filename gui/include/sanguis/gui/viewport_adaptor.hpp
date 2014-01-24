#ifndef SANGUIS_GUI_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SANGUIS_GUI_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{

class viewport_adaptor
{
	FCPPT_NONCOPYABLE(
		viewport_adaptor
	);
public:
	SANGUIS_GUI_SYMBOL
	viewport_adaptor(
		sge::renderer::device::core &,
		sge::viewport::manager &,
		sge::rucksack::widget::base &
	);

	SANGUIS_GUI_SYMBOL
	~viewport_adaptor();
private:
	sge::rucksack::widget::viewport_adaptor impl_;
};

}
}

#endif
