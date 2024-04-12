#include "iftImage.h"

#define iftCopyVoxelSize(src, dst) (dst)->dx = (src)->dx; (dst)->dy = (src)->dy; (dst)->dz = (src)->dz;

iftImage *iftThreshold(iftImage *img, int lowest, int highest, int value);
