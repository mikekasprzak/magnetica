g++ -DALLEGRO_STATICLINK src/Main.cpp src/PolyMap.cpp -o PolyMapper.exe -I src src/Math/Real.cpp src/Math/Vector/Vector2D.cpp src/Math/Matrix/Matrix2x2.cpp src/Math/Matrix/Matrix3x3.cpp -lalleg_s -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound
