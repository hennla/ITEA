#ifndef IMAGES_H
#define IMAGES_H

#include <QMap>
#include <QImage>
#include <QString>

class Images
{
public:
    Images();
    void load();
    QImage& get( const QString& imgName );
    bool isLoaded();
private:
    QMap<QString, QImage> images;
    bool isLoaded_;
};

extern Images pictures_;

#endif // IMAGES_H
