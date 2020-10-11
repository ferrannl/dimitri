#pragma once
#include "../../Engines/Audio/src/Controllers/AudioController.h"
#include <chrono>
#include <thread>
#include "../../Engines/Graphics/src/Adapters/BasePathAdapter.h"

using namespace std::this_thread;
using namespace std::chrono_literals;

class AudioDemo {
private:
	std::unique_ptr<Controllers::AudioController> _audio_controller;
public:
	AudioDemo();
	void play_music() const;
	void play_sound() const;
};