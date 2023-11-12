//
// Created by Miles on 11/6/2023.
//

#pragma once

class SoundPlayer {
public:
    enum class SoundId {
        SELECTION, ACCEPT
    };

    static SoundPlayer &getInstance() {
        static SoundPlayer soundPlayer;
        return soundPlayer;
    }

    SoundPlayer(const SoundPlayer &) = delete;

    SoundPlayer(SoundPlayer &&) = delete;

    SoundPlayer &operator=(const SoundPlayer &) = delete;

    SoundPlayer &operator=(SoundPlayer &&) = delete;

    ~SoundPlayer() {
        Mix_FreeChunk(this->soundBoard[SoundPlayer::SoundId::SELECTION]);
        Mix_FreeChunk(this->soundBoard[SoundPlayer::SoundId::ACCEPT]);
    }

    void playSound(SoundPlayer::SoundId id) {
        Mix_PlayChannel(-1, this->soundBoard.at(id), 0);
        Mix_ChannelFinished(nullptr);
    }

private:
    std::unordered_map<SoundPlayer::SoundId, Mix_Chunk *> soundBoard;

    void loadSound(const SoundPlayer::SoundId id, const char *name) {
        this->soundBoard.insert(std::make_pair(id, Mix_LoadWAV(
                std::string_view(PROJECT_PATH + R"(\assets\audio\sfx\)" + name + ".wav").data())));
        if (this->soundBoard.at(id) == nullptr) {
            std::clog << "Error loading sound: " << SDL_GetError() << '\n';
            SDL_ClearError();
            std::terminate();
        }
    }

    SoundPlayer() {
        this->loadSound(SoundPlayer::SoundId::SELECTION, "selection");
        this->loadSound(SoundPlayer::SoundId::ACCEPT, "accept");
    }
};