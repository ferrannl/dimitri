#include "AudioDemo.h"

AudioDemo::AudioDemo()
{
    _audio_controller = std::make_unique<Controllers::AudioController>();
    std::string* name = new std::string{ "music" }; 
}

void AudioDemo::play_music() const
{
	const std::string name = std::string("music");
    _audio_controller->add_music(name, (SDL_GetBasePath() + std::string{ "assets/audio/beat.wav" }).c_str());
    _audio_controller->play_audio(name);
	sleep_for(5000ms);
    _audio_controller->pause_audio(name);
	sleep_for(1000ms);
    _audio_controller->resume_audio(name);
	sleep_for(5000ms);
    _audio_controller->stop_audio(name);
}

void AudioDemo::play_sound() const
{
	const std::string name = std::string("sound");
	_audio_controller->add_sound(name, (SDL_GetBasePath() + std::string{ "assets/audio/beat.wav" }).c_str());
	_audio_controller->play_audio(name);
	sleep_for(1000ms);
	_audio_controller->pause_audio(name);
	sleep_for(1000ms);
	_audio_controller->resume_audio(name);
	sleep_for(1000ms);
	_audio_controller->stop_audio(name);
}
