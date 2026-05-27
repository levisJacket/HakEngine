
class Vertex{
    float x, y, z;
    Vertex(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
    }
}

class Calc{

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
    float fFovRad = 1.0f;

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    matProj.m[2][3] = 1.0f;
    matProj.m[3][3] = 0.0f;

}
