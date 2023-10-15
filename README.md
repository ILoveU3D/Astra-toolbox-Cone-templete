### Using Astra-toolbox With Cpp
Astra-toolbox is an advanced framework for general CT reconstruction. However, It only provides the inferences of `Python` and `MATLAB`. Actually, it still uses `C++` for its lower layer, and `CUDA` is also used for GPU acceleration. In `Python` upper inference, for instance, it used `Cython` for secondary decoration. In this repository, we do sort of works like "deconstruction", where we use `C++` and `XML` to describe the CT reconstruction parameters directly. 

In this repository, we focus on the way in **Conebeam reconstruction**, which is the most widely used measure in medical service. In Astra-toolbox, there are 2 ways to describe the geometry: **Cone** and **Cone vec**, where the details can be seen in [3D Geometry Documentation](http://www.astra-toolbox.com/docs/geom3d.html). Here we use `XML` to describe geometry parameters, the rule of XML structure can be inferred in functions *createConeXMLDocument* and *createConeVecXMLDocument* in [this file](./src/ConeProjector.cpp). As to algorithms, we provide 4 algorithms including **forward/backward projection, FDK, and SIRT**. Astra-toolbox provides more algorithms in its implementation and we can easily extend some new algorithms based on CUDA. 

Before use, you are recommended to install some extensions of `C++` including `rapidxml` and `boost`.

For more, in [main](./main.cpp), we provide a demo of Cone geometry and its forward/backward algorithm. The parameters are listed as follows:
- detector size：1000 * 200 mm
- pixel size：1 * 1 mm
- views：360, from 0 to 360 divided equally
- distance from source to detector：1000 mm
- volume size：512 * 512 * 72 pixel

If you think this repository is usable, welcome to mark it then you can look for this on your own page. If you have any questions, you can ask in Issue or contact me at quinnywang@foxmail.com, China. 

#### Inference
W. van Aarle, W. J. Palenstijn, J. Cant, E. Janssens, F. Bleichrodt, A. Dabravolski, J. De Beenhouwer, K. J. Batenburg, and J. Sijbers, “Fast and Flexible X-ray Tomography Using the ASTRA Toolbox”, Optics Express, 24(22), 25129-25147, (2016), http://dx.doi.org/10.1364/OE.24.025129
