#pragma once
#include <iostream>
#include <thread>
#include <mutex>

namespace dae
{
	using soundId = unsigned short;
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;

		virtual void Play(const soundId id, const int volume) = 0;
		virtual void AddSound(const std::string& soundName) = 0;
		virtual void MuteUnmuteSound() = 0;
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		void AddSound(const std::string& soundName) override;
		void Play(const soundId id, const int volume) override;
		void MuteUnmuteSound() override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};

	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SDLSoundSystem> m_pRealSs;
	public:
		LoggingSoundSystem(std::unique_ptr<SDLSoundSystem>&& ss) : m_pRealSs(std::move(ss)) {}
		virtual ~LoggingSoundSystem() override = default;

		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;

		void Play(const soundId id, const int volume = 1) override
		{
			m_pRealSs->Play(id, volume);
			std::cout << "playing " << id << " at volume " << volume << std::endl;
		}

		void AddSound(const std::string& soundName) override
		{
			m_pRealSs->AddSound(soundName);
			std::cout << "adding sound: " << soundName << std::endl;
		}

		void MuteUnmuteSound() override
		{
			m_pRealSs->MuteUnmuteSound();
			std::cout << "muting/unmuting sound\n";
		}
	};

	class NullSoundSystem final : public SoundSystem
	{
		void Play(const soundId, const int) override {}
		void AddSound(const std::string&) override {}
		void MuteUnmuteSound() override {}
	};

	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> m_pSsInstance;
	public:
		static SoundSystem& GetSoundSystem() { return *m_pSsInstance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
		{
			m_pSsInstance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}
	};
}