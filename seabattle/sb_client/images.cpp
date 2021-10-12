#include "images.h"

Images pictures_ = Images();

Images::Images() : isLoaded_(false){
}

void Images::load() {
    if( isLoaded_ ) {
        return;
    }
    images.insert("field", QImage(":/background.png"));
    images.insert("dot", QImage(":/dot.png"));
    images.insert("deck", QImage(":/deck.png"));
    images.insert("half", QImage(":/half.png"));
    images.insert("redhalf", QImage(":/redhalf.png"));
    images.insert("full", QImage(":/full.png"));
    images.insert("redfull", QImage(":/redfull.png"));
    isLoaded_ = true;
}

bool Images::isLoaded() {
    return isLoaded_;
}

QImage& Images::get( const QString& imgName ) {
    QMap<QString, QImage>::Iterator it = images.find(imgName);

    if (it == images.end()) {
        QString err = "Image " + imgName + " not found";
        throw std::runtime_error(err.toStdString());
    }

    return it.value();
}
