#include "pch.h"
#include "AudioSystem.h"

nc::AudioSystem g_audioSystem;

namespace nc {

	void nc::AudioSystem::Startup()
	{
		FMOD::System_Create(&m_system);
		void* extradriverdata = nullptr;
		m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void nc::AudioSystem::Shutdown()
	{
		for (auto& sound : m_sounds) {
			sound.second->release();
		}
		m_sounds.clear();
		m_system->close();
		m_system->release();
	}

	void nc::AudioSystem::Update(float dt)
	{
		m_system->update();
	}

	void nc::AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{
		if (m_sounds.find(name) == m_sounds.end()) {
			FMOD::Sound* sound{ nullptr };
			m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			m_sounds[name] = sound;
		}
	}

	void nc::AudioSystem::PlayAudio(const std::string& name)
	{
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end()) {
			FMOD::Sound* sound = iter->second;
			sound->setMode(FMOD_LOOP_OFF);
			FMOD::Channel* channel; m_system->playSound(sound, 0, false, &channel);
		}
	}

}
