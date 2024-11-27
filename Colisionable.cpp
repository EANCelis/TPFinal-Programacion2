#include "Colisionable.h"


bool Colisionable::colisiono(Colisionable &col) const {
    return getBounds().intersects(col.getBounds());
}
