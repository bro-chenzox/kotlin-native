/*
 * Copyright 2010-2021 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license
 * that can be found in the LICENSE file.
 */

#ifndef RUNTIME_MM_MARK_AND_SWEEP_H
#define RUNTIME_MM_MARK_AND_SWEEP_H

#include <cstddef>

#include "Utils.hpp"

namespace kotlin {
namespace mm {

// Stop-the-world Mark-and-Sweep.
class MarkAndSweep : private Pinned {
public:
    class ObjectData {
    public:
        enum class Color {
            kWhite = 0, // Initial color at the start of collection cycles. Objects with this color at the end of GC cycle are collected.
                        // All new objects are allocated with this color.
            kBlack, // Objects encountered during mark phase.
        };

        Color color() const noexcept { return color_; }
        void setColor(Color color) noexcept { color_ = color; }

    private:
        Color color_;
    };

    class ThreadData : private Pinned {
    public:
        using ObjectData = MarkAndSweep::ObjectData;

        explicit ThreadData(MarkAndSweep& gc) noexcept;
        ~ThreadData() = default;

        void SafePointFunctionEpilogue() noexcept;
        void SafePointLoopBody() noexcept;
        void SafePointExceptionUnwind() noexcept;
        void SafePointAllocation(size_t size) noexcept;

        void PerformFullGC() noexcept;

        void OnOOM(size_t size) noexcept;

    private:
    };

    MarkAndSweep() noexcept;
    ~MarkAndSweep();

private:
};

} // namespace mm
} // namespace kotlin

#endif // RUNTIME_MM_MARK_AND_SWEEP_H
