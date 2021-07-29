#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <memory>

class Media {
public:
    void addMediaSharing(std::ostream &mediaSharing) {
        mediaSharingVector.push_back(&mediaSharing);
    }

    void print(std::string mediaString) {
        for (auto &stream : mediaSharingVector) {
            *stream << transformMedia(mediaString) << std::endl;
        }
    }

protected:
    std::vector<std::ostream *> mediaSharingVector;

    virtual std::string transformMedia(std::string mediaString) = 0;
};

class UpperRegisterMedia : public Media {
protected:
    std::string transformMedia(std::string mediaString) override {
        std::transform(mediaString.begin(), mediaString.end(), mediaString.begin(), ::toupper);
        return mediaString;
    }
};

class UnderscoreSplitterMedia : public Media {
protected:
    std::string transformMedia(std::string mediaString) override {
        std::replace(mediaString.begin(), mediaString.end(), ' ', '_');
        return mediaString;
    }

};

class OriginalMedia : public Media {
protected:
    std::string transformMedia(std::string mediaString) override {
        {
            return mediaString;
        }
    }
};

class ZMI {
public:
    void addZmi(Media &media) {
        mediaVector.push_back(&media);
    }

    friend ZMI operator<<(ZMI zmi, std::string mediaString) {
        for (auto media : zmi.mediaVector) {
            media->print(mediaString);
        }
        return zmi;
    }

private:
    std::vector<Media *> mediaVector;

};

int main() {
    std::ofstream fileOut("D:\\GIT\\ITEA\\HW5\\SomeNews.txt");
    UpperRegisterMedia upperRegisterMedia;
    upperRegisterMedia.addMediaSharing(std::cout);
    upperRegisterMedia.addMediaSharing(std::cerr);
    upperRegisterMedia.addMediaSharing(fileOut);

    UnderscoreSplitterMedia underscoreSplitterMedia;

    underscoreSplitterMedia.addMediaSharing(fileOut);
    underscoreSplitterMedia.addMediaSharing(std::cout);

    OriginalMedia originalMedia;
    originalMedia.addMediaSharing(std::cout);

    ZMI zmi;
    zmi.addZmi(upperRegisterMedia);
    zmi.addZmi(underscoreSplitterMedia);
    zmi.addZmi(originalMedia);
    //Breaking news. Robbery at the bank
    zmi << "Breaking news. Robbery at the bank";
    return 0;
}
