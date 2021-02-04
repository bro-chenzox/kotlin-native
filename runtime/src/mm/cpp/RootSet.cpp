/*
 * Copyright 2010-2021 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license
 * that can be found in the LICENSE file.
 */

#include "RootSet.hpp"

using namespace kotlin;

mm::RootSet::ThreadRootSetIterator::ThreadRootSetIterator(begin_t, ThreadData& threadData) noexcept;

mm::RootSet::ThreadRootSetIterator::ThreadRootSetIterator(end_t, ThreadData& threadData) noexcept;

ObjHeader* mm::RootSet::ThreadRootSetIterator::operator*() const noexcept;

ThreadRootSetIterator& mm::RootSet::ThreadRootSetIterator::operator++() noexcept;

bool mm::RootSet::ThreadRootSetIterator::operator==(const ThreadRootSetIterator& rhs) const noexcept;

mm::RootSet::GlobalRootSetIterator::GlobalRootSetIterator(begin_t) noexcept;

mm::RootSet::GlobalRootSetIterator::GlobalRootSetIterator(end_t) noexcept;

ObjHeader* mm::RootSet::GlobalRootSetIterator::operator*() const noexcept;

GlobalRootSetIterator& mm::RootSet::GlobalRootSetIterator::operator++() noexcept;

bool mm::RootSet::GlobalRootSetIterator::operator==(const GlobalRootSetIterator& rhs) const noexcept;

void mm::RootSet::Publish(ThreadData& threadData) noexcept;
