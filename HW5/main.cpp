#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <memory>

class Media {
public:
    void addMediaSharing(const std::shared_ptr<std::ostream>& mediaSharing) {
        mediaSharingVector.push_back(mediaSharing);
    }

    void print(const std::string& mediaString) {
        for (auto &stream : mediaSharingVector) {
            *stream << transformMedia(mediaString) << std::endl;
        }
    }

protected:
    std::vector<std::shared_ptr<std::ostream>> mediaSharingVector;

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
    void addZmi(const std::shared_ptr<Media>& media) {
        mediaVector.push_back(media);
    }

    friend ZMI operator<<(ZMI zmi, const std::string& mediaString) {
        for (const auto& media : zmi.mediaVector) {
            media->print(mediaString);
        }
        return zmi;
    }

private:
    std::vector<std::shared_ptr<Media>> mediaVector;

};

int main() {
    std::ofstream fileOut(R"(D:\GIT\ITEA\HW5\SomeNews.txt)");
    UpperRegisterMedia upperRegisterMedia;
    upperRegisterMedia.addMediaSharing(std::shared_ptr<std::ostream>(&std::cout, [](void*) {}));
    upperRegisterMedia.addMediaSharing(std::shared_ptr<std::ostream>(&std::cerr, [](void*) {}));
    upperRegisterMedia.addMediaSharing(std::shared_ptr<std::ostream>(&fileOut, [](void*) {}));

    UnderscoreSplitterMedia underscoreSplitterMedia;

    underscoreSplitterMedia.addMediaSharing(std::shared_ptr<std::ostream>(&fileOut, [](void*) {}));
    underscoreSplitterMedia.addMediaSharing(std::shared_ptr<std::ostream>(&std::cout, [](void*) {}));

    OriginalMedia originalMedia;
    originalMedia.addMediaSharing(std::shared_ptr<std::ostream>(&std::cout, [](void*) {}));

    ZMI zmi;
    zmi.addZmi(std::make_shared<UpperRegisterMedia>(upperRegisterMedia));
    zmi.addZmi(std::make_shared<UnderscoreSplitterMedia>(underscoreSplitterMedia));
    zmi.addZmi(std::make_shared<OriginalMedia>(originalMedia));
    //Breaking news. Robbery at the bank
    zmi << "Breaking news. Robbery at the bank";
    return 0;
}