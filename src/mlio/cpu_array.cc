/*
 * Copyright 2019-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not use this file except in compliance with the License. A copy of
 * the License is located at
 *
 *      http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 */

#include "mlio/cpu_array.h"

namespace mlio {
inline namespace abi_v1 {
namespace detail {
namespace {

template<Data_type dt>
struct make_cpu_array_op {
    std::unique_ptr<Device_array> operator()(std::size_t size)
    {
        return Cpu_array_access::wrap(dt, std::vector<data_type_t<dt>>(size));
    }
};

}  // namespace
}  // namespace detail

std::unique_ptr<Device_array> make_cpu_array(Data_type dt, std::size_t size)
{
    return dispatch<detail::make_cpu_array_op>(dt, size);
}

}  // namespace abi_v1
}  // namespace mlio
