#ifndef ONEFLOW_CORE_KERNEL_CUDA_RING_ALL_REDUCE_KERNEL_H_
#define ONEFLOW_CORE_KERNEL_CUDA_RING_ALL_REDUCE_KERNEL_H_

#include "oneflow/core/kernel/kernel.h"

namespace oneflow {

constexpr int32_t CUDA_RING_ALL_REDUCE_MAX_NUM_RINGS = 8;

template<typename T>
struct CudaRingAllReduceArg {
  int32_t num_rings;
  T* send[CUDA_RING_ALL_REDUCE_MAX_NUM_RINGS];
  const T* recv[CUDA_RING_ALL_REDUCE_MAX_NUM_RINGS];
  T* dst[CUDA_RING_ALL_REDUCE_MAX_NUM_RINGS];
  const T* src[CUDA_RING_ALL_REDUCE_MAX_NUM_RINGS];
  int64_t num_elem[CUDA_RING_ALL_REDUCE_MAX_NUM_RINGS];
};

template<typename T>
class CudaRingAllReduceKernel final : public KernelIf<DeviceType::kGPU> {
 public:
  OF_DISALLOW_COPY_AND_MOVE(CudaRingAllReduceKernel);
  CudaRingAllReduceKernel() = default;
  ~CudaRingAllReduceKernel() override = default;

 private:
  void VirtualKernelInit(const ParallelContext*) override;
  void Forward(const KernelCtx&, std::function<Blob*(const std::string&)>) const override;
};

template<typename T>
struct CudaRingAllReduceKernelUtil {
  static void Send(DeviceCtx* ctx, CudaRingAllReduceArg<T> arg);
  static void RecvReduceSend(DeviceCtx* ctx, CudaRingAllReduceArg<T> arg);
  static void RecvReduceSendCopy(DeviceCtx* ctx, CudaRingAllReduceArg<T> arg);
  static void RecvSendCopy(DeviceCtx* ctx, CudaRingAllReduceArg<T> arg);
  static void RecvCopy(DeviceCtx* ctx, CudaRingAllReduceArg<T> arg);
};

}  // namespace oneflow

#endif  // #define ONEFLOW_CORE_KERNEL_CUDA_RING_ALL_REDUCE_KERNEL_H_
