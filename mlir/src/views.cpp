#include <gap/mlir/views.hpp>

namespace gap::mlir::views
{
    auto regions(operation op) -> decltype(std::views::all(op->getRegions())) {
        return op->getRegions() | std::views::all;
    }

    auto blocks(operation op) -> decltype(std::views::join(regions(op))) {
        return regions(op) | std::views::join;
    }

    auto operations(operation op) -> decltype(std::views::join(blocks(op))) {
        return blocks(op) | std::views::join;
    }

} // namespace gap::mlir::views