/***************************************************************************
* 
* Copyright (c) 2022 Baidu, Inc.  All Rights Reserved.
* 
**************************************************************************/
/**
* @file replication_pad.h
* @author tianjinjin@baidu.com
* @date Tue Sep  7 14:29:20 CST 2021
* @brief 
**/

#pragma once

#include <string>

//from pytorch
#include "torch/script.h"

#include "poros/converter/gpu/gpu_converter.h"
#include "poros/engine/tensorrt_engine.h"

namespace baidu {
namespace mirana {
namespace poros {

class ReplicationPadConverter : public GpuConverter {
public:
    ReplicationPadConverter() {}
    virtual ~ReplicationPadConverter() {}

    bool converter(TensorrtEngine* engine, const torch::jit::Node *node);

    const std::vector<std::string> schema_string() {
        return {"aten::replication_pad1d(Tensor self, int[2] padding) -> Tensor",
                "aten::replication_pad2d(Tensor self, int[4] padding) -> Tensor",
                "aten::replication_pad3d(Tensor self, int[6] padding) -> Tensor",
                };
    }

    /** TODO: TO SUPPORT CONVERTERS BELLOW:
     * "aten::replication_pad1d.out(Tensor self, int[2] padding, *, Tensor(a!) out) -> Tensor(a!)",
     * "aten::replication_pad2d.out(Tensor self, int[4] padding, *, Tensor(a!) out) -> Tensor(a!)",
     * "aten::replication_pad3d.out(Tensor self, int[6] padding, *, Tensor(a!) out) -> Tensor(a!)"
     * **/
    const std::vector<torch::jit::NodeKind> node_kind() {
        return {torch::jit::aten::replication_pad1d,
                torch::jit::aten::replication_pad2d,
                torch::jit::aten::replication_pad3d,
                };
    }
};

}  // namespace poros 
}  // namespace mirana
}  // namespace baidu
