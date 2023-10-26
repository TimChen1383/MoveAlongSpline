# MoveAlongSpline
Moving object along the spline. The path of object movement is controlled by a custom curve. When the object has been overlapped, timeline will be triggered and the object will move along the spline.

 To make it works you need to to followings :
- Assigned a platform mesh in the details panel as it will be the mesh that move along the spline
- Stretching a custom object moving path with the spline component that has been provided
- Add a curve float to the “TimeCurveFloat” slot in the details panel. This will be used for controlling the lerp value in timeline
- Use “PlatformSpeed” in the details panel to control the moving speed of the platform
- Ready to go


![MoveAlongSpline](https://github.com/TimChen1383/MoveAlongSpline_UE/assets/37008451/08a221e5-ee98-4b25-9d87-de9d57f0873f)
