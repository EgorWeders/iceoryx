// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
// Copyright (c) 2021 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "iceoryx_posh/internal/popo/ports/server_port_data.hpp"

namespace iox
{
namespace popo
{
ServerPortData::ServerPortData(const capro::ServiceDescription& serviceDescription,
                               const RuntimeName_t& runtimeName,
                               const ServerOptions& serverOptions,
                               mepoo::MemoryManager* const memoryManager,
                               const mepoo::MemoryInfo& memoryInfo) noexcept
    : BasePortData(serviceDescription, runtimeName, serverOptions.nodeName)
    , m_chunkSenderData(
          memoryManager, static_cast<SubscriberTooSlowPolicy>(serverOptions.clientTooSlowPolicy), 0, memoryInfo)
    , m_chunkReceiverData(cxx::VariantQueueTypes::SoFi_MultiProducerSingleConsumer,
                          QueueFullPolicy::DISCARD_OLDEST_DATA)
    , m_offeringRequested(serverOptions.offerOnCreate)
{
    m_chunkReceiverData.m_queue.setCapacity(serverOptions.requestQueueCapacity);
}

} // namespace popo
} // namespace iox
