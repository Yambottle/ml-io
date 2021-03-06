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

#pragma once

#include <optional>

#include "mlio/config.h"
#include "mlio/fwd.h"
#include "mlio/intrusive_ptr.h"
#include "mlio/record_readers/stream_record_reader.h"

namespace mlio {
inline namespace abi_v1 {

/// @addtogroup records Records
/// @{

/// Represents an abstract helper base class for reading text-based
/// records from an @ref Input_stream.
class MLIO_API Text_record_reader : public Stream_record_reader {
protected:
    explicit Text_record_reader(Intrusive_ptr<Input_stream> stream);

private:
    MLIO_HIDDEN
    std::optional<Record> decode_record(Memory_slice &chunk, bool ignore_leftover) final;

    /// When implemented in a derived class, tries to decode a Record
    /// from the specified chunk.
    ///
    /// @param chunk
    ///     A memory slice that contains one or more records. The chunk
    ///     is guaranteed to have no Unicode BOM bits.
    /// @param ignore_leftover
    ///     A boolean value indicating whether to ignore any leftover
    ///     bits than cannot be interpreted as a Record. If false, the
    ///     reader should throw an exception with a descriptive message.
    virtual std::optional<Record> decode_text_record(Memory_slice &chunk, bool ignore_leftover) = 0;

    MLIO_HIDDEN
    static bool skip_utf8_bom(Memory_slice &chunk, bool ignore_leftover) noexcept;
};

/// @}

}  // namespace abi_v1
}  // namespace mlio
