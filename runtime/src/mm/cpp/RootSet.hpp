/*
 * Copyright 2010-2021 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license
 * that can be found in the LICENSE file.
 */

#ifndef RUNTIME_MM_ROOT_SET_H
#define RUNTIME_MM_ROOT_SET_H

struct ObjHeader;

namespace kotlin {
namespace mm {

class ThreadData;

class RootSet {
public:
    class ThreadRootSetIterator {
    public:
        struct begin_t {};
        static constexpr inline begin_t begin = begin_t{};

        struct end_t {};
        static constexpr inline end_t end = end_t{};

        ThreadRootSetIterator(begin_t, ThreadData& threadData) noexcept;
        ThreadRootSetIterator(end_t, ThreadData& threadData) noexcept;

        ObjHeader* operator*() const noexcept;

        ThreadRootSetIterator& operator++() noexcept;

        bool operator==(const ThreadRootSetIterator& rhs) const noexcept;

        bool operator!=(const ThreadRootSetIterator& rhs) const noexcept {
            return !(*this == rhs);
        }
    };

    class ThreadRootSetIterable {
    public:
        ThreadRootSetIterable(ThreadData& threadData) noexcept : threadData_(threadData) {}

        ThreadRootSetIterator begin() noexcept { return ThreadRootSetIterator(ThreadRootSetIterator::begin, threadData_); }
        ThreadRootSetIterator end() noexcept { return ThreadRootSetIterator(ThreadRootSetIterator::end, threadData_); }

    private:
        ThreadData& threadData_;
    };

    class GlobalRootSetIterator {
    public:
        struct begin_t {};
        static constexpr inline begin_t begin = begin_t{};

        struct end_t {};
        static constexpr inline end_t end = end_t{};

        GlobalRootSetIterator(begin_t) noexcept;
        GlobalRootSetIterator(end_t) noexcept;

        ObjHeader* operator*() const noexcept;

        GlobalRootSetIterator& operator++() noexcept;

        bool operator==(const GlobalRootSetIterator& rhs) const noexcept;

        bool operator!=(const GlobalRootSetIterator& rhs) const noexcept {
            return !(*this == rhs);
        }
    };

    class GlobalRootSetIterable {
    public:
        GlobalRootSetIterator begin() noexcept { return GlobalRootSetIterator(GlobalRootSetIterator::begin); }
        GlobalRootSetIterator end() noexcept { return GlobalRootSetIterator(GlobalRootSetIterator::end); }
    };

    void Publish(ThreadData& threadData) noexcept;

    ThreadRootSetIterable ThreadIter(ThreadData& threadData) noexcept { return ThreadRootSetIterable(threadData); }

    GlobalRootSetIterable GlobalIter() noexcept { return GlobalRootSetIterable(); }

private:
};

} // namespace mm
} // namespace kotlin

#endif // RUNTIME_MM_ROOT_SET_H
