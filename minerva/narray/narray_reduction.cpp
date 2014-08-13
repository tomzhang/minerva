#include "narray.h"
#include "op/shared_op.h"
#include <iostream>

using namespace std;

namespace minerva {

// Lazy reductions
NArray NArray::Sum(int dim) {
  return Sum(Scale{dim});
}

NArray NArray::Sum(const Scale& dims) {
  auto size = Size();
  for (auto i: dims) {
    size[i] = 1;
  }
  ReductionOp* reduction_op = new ReductionOp;
  reduction_op->closure.type = SUM;
  reduction_op->closure.dims_to_reduce = dims;
  return NArray::Compute({*this}, {size}, reduction_op)[0];
}

NArray NArray::Max(int dim) {
  return Max(Scale{dim});
}

NArray NArray::Max(const Scale& dims) {
  auto size = Size();
  for (auto i: dims) {
    size[i] = 1;
  }
  ReductionOp* reduction_op = new ReductionOp;
  reduction_op->closure.type = MAX;
  reduction_op->closure.dims_to_reduce = dims;
  return NArray::Compute({*this}, {size}, reduction_op)[0];
}

NArray NArray::MaxIndex(int dim) {
  auto size = Size();
  size[dim] = 1;
  MaxIndexOp* op = new MaxIndexOp;
  op->closure.dim = dim;
  return NArray::Compute({*this}, {size}, op)[0];
}

// Non-lazy reduction
float NArray::Sum() {
  // TODO
  return 0;
}
float NArray::Max() {
  // TODO
  return 0;
}

int NArray::CountZero() {
  int* value = reinterpret_cast<int*>(Get());
  int size = Size().Prod();
  int counter = 0;
  for (int i = 0; i < size; ++i) {
    if (!value[i]) {
      ++counter;
    }
  }
  return counter;
}

} // end of namespace minerva

