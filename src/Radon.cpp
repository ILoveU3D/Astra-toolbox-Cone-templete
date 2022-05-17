#include"../include/Radon.h"
#include"../astra-2.1.0/astra/CudaForwardProjectionAlgorithm3D.h"
#include"../astra-2.1.0/astra/CudaBackProjectionAlgorithm3D.h"
#include"../astra-2.1.0/astra/CudaFDKAlgorithm3D.h"

namespace Transform{
    void createForwardProjection(CFloat32ProjectionData3D *sino, CFloat32VolumeData3D* volume, CProjector3D *projector){
        CCudaForwardProjectionAlgorithm3D *algorithm = new CCudaForwardProjectionAlgorithm3D();
        algorithm->initialize(projector, sino, volume, 0);
        algorithm->run();
    }
    void createBackProjection(CFloat32ProjectionData3D *sino, CFloat32VolumeData3D* volume, CProjector3D *projector){
        CCudaBackProjectionAlgorithm3D *algorithm = new CCudaBackProjectionAlgorithm3D();
        algorithm->initialize(projector, sino, volume);
        algorithm->run();
    }
    void FDK(CFloat32ProjectionData3D *sino, CFloat32VolumeData3D* volume, CProjector3D *projector){
        CCudaFDKAlgorithm3D *algorithm = new CCudaFDKAlgorithm3D();
        algorithm->initialize(projector, sino, volume);
        algorithm->run();
    }

}