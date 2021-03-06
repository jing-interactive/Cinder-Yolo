# Cinder-Yolo

Cinder block for running Darknet's YoloV3 object detection. This block uses the following fork of Darknet https://github.com/AlexeyAB/darknet

Tested on macOS with Cuda 10 and cuDNN 7.3.1. There is an issue with CMake's `FindCuda` when Cuda version >= 10.0 and CMake version <= 3.12.1 thus you are going to need a CMake version >= 3.12.2 in order for this to work.

You will have to download the pre-trained weights separately. For normal v3 [here](https://pjreddie.com/media/files/yolov3.weights) or for tiny version [here](https://pjreddie.com/media/files/yolov3-tiny.weights)

Build Cinder and then from Cinder's root folder run:

```
cd Cinder-Yolo/samples/BasicSample/proj/cmake && \
mkdir build && cd build && \
cmake .. -DUSE_GPU=ON && \
make -j4
```
