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
		virtual ~SoundSystem() = default;
		virtual void Play(const soundId id, const int volume) = 0;
		virtual void AddSound(const std::string& soundName) = 0;
		virtual void MuteUnmuteSound() = 0;
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		void AddSound(const std::string& soundName) override;
		void Play(const soundId id, const int volume) override;
		void MuteUnmuteSound() override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};

	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SDLSoundSystem> RealSs;
	public:
		LoggingSoundSystem(std::unique_ptr<SDLSoundSystem>&& ss) : RealSs(std::move(ss)) {}
		virtual ~LoggingSoundSystem() override = default;

		void Play(const soundId id, const int volume = 1) override
		{
			RealSs->Play(id, volume);
			std::cout << "playing " << id << " at volume " << volume << std::endl;
		}

		void AddSound(const std::string& soundName) override
		{
			RealSs->AddSound(soundName);
			std::cout << "adding sound: " << soundName << std::endl;
		}

		void MuteUnmuteSound() override
		{
			RealSs->MuteUnmuteSound();
			std::cout << "muting/unmuting sound\n";
		}
	};

	class NullSoundSystem final : public SoundSystem
	{
		void Play(const soundId, const int) override {}
		void AddSound(const std::string&) override {}
		void MuteUnmuteSound() override {}
	};

	class Servicelocator final
	{
		static std::unique_ptr<SoundSystem> SsInstance;
	public:
		static SoundSystem& GetSoundSystem() { return *SsInstance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
		{
			SsInstance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}
	};
}