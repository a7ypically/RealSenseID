// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2020-2021 Intel Corporation. All Rights Reserved.

#pragma once

#include "RealSenseID/Preview.h"
#include "RawHelper.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

#ifdef ANDROID
#include "AndroidCapture.h"
#elif LINUX
#include "LinuxCapture.h"
#elif _WIN32
#include "MSMFCapture.h"
#endif

namespace RealSenseID
{
class PreviewImpl
{
public:
    ~PreviewImpl();
    explicit PreviewImpl(const PreviewConfig& config);
    bool StartPreview(PreviewImageReadyCallback& callback);
    bool PausePreview();
    bool ResumePreview();
    bool StopPreview();

private:
    PreviewConfig _config;
    std::thread _worker_thread;
    std::atomic_bool _canceled {false};
    std::atomic_bool _paused {false};
    std::mutex _m;
    std::condition_variable _cv;
    PreviewImageReadyCallback* _callback = nullptr;
    std::unique_ptr<Capture::CaptureHandle> _capture;
    std::unique_ptr<Capture::RawHelper> _raw_helper;
};
} // namespace RealSenseID
