#ifndef SETTINGS_H
#define SETTINGS_H

#include "ISettings.h"
#include <string>
#include <memory>

namespace jukebox { namespace settings {

struct PImpl;

class Settings : public ISettings
{
public:
    Settings(std::string musicDirectory_);
    ~Settings() override;

    std::string getMusicDirectory() const override;
    void setMusicDirectory(std::string musicDirectory) override;
    int getTimeToPlaySong() const override;
    void setTimeToPlaySong(int millisecsToPlaySong) override;
    int getTimeToSaveInsertedCoins() const override;
    void setTimeToSaveInsertedCoins(int millisecs) override;

private:
    void serialize();
    void deserialize();

    std::unique_ptr<PImpl> data;
};

}}

#endif //SETTINGS_H
