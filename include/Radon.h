#include"../astra-2.1.0/astra/Float32ProjectionData3D.h"
#include"../astra-2.1.0/astra/Float32VolumeData3D.h"
#include"../astra-2.1.0/astra/Projector3D.h"
using namespace astra;

namespace Transform{
    void createForwardProjection(CFloat32ProjectionData3D *sino, CFloat32VolumeData3D* volume, CProjector3D *projector);
    void createBackProjection(CFloat32ProjectionData3D *sino, CFloat32VolumeData3D* volume, CProjector3D *projector);
    void FDK(CFloat32ProjectionData3D *sino, CFloat32VolumeData3D* volume, CProjector3D *projector);
    void ART(CFloat32ProjectionData3D *sino, CFloat32VolumeData3D* volume, CProjector3D *projector);
}